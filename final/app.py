import secrets
import math

from flask import Flask, redirect, render_template, request, session
from flask_session import Session
import random
# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
app.secret_key = secrets.token_hex(16)
Session(app)

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    """ Obtain number of people user wishes to have grouped"""
    if request.method == "POST":
        people = int(request.form.get("people"))
        session['people'] = people
        return render_template("input.html", people=people)
    else:
        return render_template("index.html")

@app.route("/input", methods=["GET", "POST"])
def input():
    """Use the info from the table to generate random groups"""
    if request.method == "POST":
        # Extract number of groups
        num_groups = int(request.form.get("groups"))
        session['num_groups'] = num_groups
        # Create empty array and empty dictionary for names and preferences
        names = []
        preferences = {}
        dispreferences = {}
        people = session.get('people')
        # Get names and add to array
        for i in range(people):
            name = request.form.get(f"name{i}")
            if name:
                names.append(name)
                preferences[name] = request.form.getlist(f"preferences{i}")
                dispreferences[name] = request.form.getlist(f"dispreferences{i}")
        # Save info to session
        session['names'] = names
        session['preferences'] = preferences
        session['dispreferences'] = dispreferences
        # Do some group creating magic in create_groups :)
        groups = create_groups(names, preferences, dispreferences, num_groups)

        return render_template("groupings.html", groups=groups)

    else:
        return redirect("/")

def create_groups(names, preferences, dispreferences, num_groups):
    # Create empty groups for number of groups requests
    groups = [[] for _ in range(num_groups)]
    # Shuffle names for randomness
    random.shuffle(names)
    people = session.get('people')

    dispreferences_associated = [] # This include anyone involved in a dispreference
    preferences_associated = [] # This include anyone involved in a dispreference
    dissociates = {}
    associates = {}
    free_names = [] # This is everyone else that's free to move

    for name in names:
        dissociated = False
        associated = False
        # Check if they are dispreferences associated
        for other_name in names:
            # If the person has a dispreference, or if they are a dispreference of someone else, append name to dispreferences dictionary
            if len(dispreferences[name]) > 0 or name in dispreferences[other_name]:
                # Record number of people this person needs to be separated from for sorting
                dissociates[name] = len(dispreferences[name])
                count = 0
                for other_name_again in names:
                    if name in dispreferences[other_name_again]:
                        count += 1
                dissociates[name] += count
                # Add this person to the dispreferences_associated array
                if name not in dispreferences_associated:
                    dispreferences_associated.append(name)
                    dissociated = True
                break
        # Check if they are preferences associated
        for other_name in names:
            # If the person is not associated with a dispreference, and if the person has a preference, or if they are a preference of someone else, append name
            if len(preferences[name]) > 0 or name in preferences[other_name]:
                # Record number of people this person needs to be separated from for sorting
                associates[name] = len(preferences[name])
                count = 0
                for other_name_again in names:
                    if name in dispreferences[other_name_again]:
                        count += 1
                associates[name] += count
                # Add this person to the preferences_associated array
                if name not in preferences_associated and name not in dispreferences_associated:
                    preferences_associated.append(name)
                    associated = True
                break
        # Only if no preferences for groups or separation, they're free to be randomized
        if not dissociated and not associated and name not in free_names:
            free_names.append(name)
    # Sort the names that are associated with preferences starting with those with most associations
    preferences_associated = sorted(preferences_associated, key=lambda name: associates[name], reverse=True)
    dispreferences_associated = sorted(dispreferences_associated, key=lambda name: dissociates[name], reverse=True)
    # Separate those that need to be separated first, finding best group
    for name in dispreferences_associated:
        best_group = best_separation(name, groups, dispreferences[name], dispreferences)
        best_group.append(name)
    # After those who must be separated are dealt with, find best groups for those with preferences
    for name in preferences_associated:
        best_group = best_join(name, groups, preferences[name], preferences)
        best_group.append(name)
    # Place the remaining free_names into any group that still has space
    for name in free_names:
        for group in groups:
            if len(group) < (math.ceil(people/num_groups)):
                group.append(name)
                break
    return groups

def best_separation(name, groups, dispreferences, other_dispreferences):
    people = session.get('people')
    num_groups = session.get('num_groups')
    best_group = None
    least_count = 1
    for group in groups:
        count = 0
        # If the group still has space
        if len(group) < (math.ceil(people/num_groups)):
            # Find how many people the person is dissociated with are in the group
            for person in group:
                if person in dispreferences or name in other_dispreferences[person]:
                    count += 1
            # If tied for least count
            if count == least_count:
                best_group = group
            # Only if there are no dissociates in the group
            if count < least_count:
                least_count = count
                best_group = group
        else:
            continue
    return best_group

def best_join(name, groups, preferences, other_preferences):
    people = session.get('people')
    num_groups = session.get('num_groups')
    best_group = None
    max_count = -1
    for group in groups:
        count = 0
        # If the group still has space
        if len(group) < (math.ceil(people/num_groups)):
            for person in group:
                if person in preferences or name in other_preferences[person]:
                    count += 1
            if count > max_count:
                max_count = count
                best_group = group
        else:
            continue
    if best_group is None:
        # If no best group, put them in the group with most spots available for the person and their preferences
        for group in groups:
            available_spots = (math.ceil(people/num_groups))-len(group)
            if available_spots > 0:
                # Find out exact needed spots
                needed_spots = len(preferences[name]) + 1
                for person in people:
                    if name in other_preferences[person] and person not in preferences[name]:
                        needed_spots += 1
                if available_spots >= needed_spots:
                    best_group = group
                    break
            else:
                continue
    return best_group

@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table, and give option to generate again"""
    # If user wants to generate again, go through all the same process from input
    if request.method == "POST":
        num_groups = session.get('num_groups')
        names = session.get('names')
        preferences = session.get('preferences')
        dispreferences = session.get('dispreferences')
        groups = create_groups(names, preferences, dispreferences, num_groups)

        return render_template("groupings.html", groups=groups)
    else:
        return redirect("/")
