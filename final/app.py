import secrets

from flask import Flask, flash, redirect, render_template, request, session
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

    preferences_associated = []
    dispreferences_associated = []
    free_names = []

    for name in names:
        dissociated = False
        associated = False
        for other_name in names:
            # If the person has a dispreference, or if they are a dispreference of someone else, append name to dispreferences dictionary
            if len(dispreferences[name]) > 0 or name in dispreferences[other_name]:
                if name not in dispreferences_associated:
                    dispreferences_associated.append(name)
                    dissociated = True
                break
        for other_name in names:
            # If the person is not associated with a dispreference, and if the person has a preference, or if they are a preference of someone else, append name
            if len(preferences[name]) > 0 or name in preferences[other_name]:
                if name not in preferences_associated and name not in dispreferences_associated:
                    preferences_associated.append(name)
                    associated = True
                break
        # Only if no preferences for groups or separation, they're free to be randomized
        if not dissociated and not associated and name not in free_names:
            free_names.append(name)
    # Sort the names that are associated with preferences starting with those with most associations
    preferences_associated = sorted(preferences_associated, key=lambda name: len(preferences[name]), reverse=True)
    dispreferences_associated = sorted(dispreferences_associated, key=lambda name: len(dispreferences[name]), reverse=True)
    print("Preferences Associated", preferences_associated)
    print("Dispreferences Associated", dispreferences_associated)
    print("Free names", free_names)
    # Separate those that need to be separated first
    for name in dispreferences_associated:
        best_group = best_separation(name, groups, dispreferences[name], dispreferences)
        best_group.append(name)
    for name in preferences_associated:
        best_group = best_join(name, groups, preferences[name], preferences)
        best_group.append(name)
    for name in free_names:
        # Just place in any group
        for group in groups:
            if len(group) < (people/num_groups):
                group.append(name)
    return groups

def best_separation(name, groups, dispreferences, other_dispreferences):
    people = session.get('people')
    num_groups = session.get('num_groups')
    best_group = None
    max_count = 1
    for group in groups:
        count = 0
        if len(group) < (people/num_groups):
            for person in group:
                if person in dispreferences or name in other_dispreferences[person]:
                    count += 1
            print(f"Group: {group}, Count: {count}, Max Count: {max_count}")
            if count == max_count:
                best_group = group
            if count < max_count:
                max_count = count
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
        if len(group) < (people/num_groups):
            for person in group:
                if person in preferences or name in other_preferences[person]:
                    count += 1
            if count > max_count:
                max_count = count
                best_group = group
        else:
            continue
    if best_group is None:
        # If no best group, put them in the group with most spots available for preferences
        # Find number of people associated with
        needed_spots = len(preferences[name]) + 1
        min_spots = needed_spots
        for group in groups:
            available_spots = (people/num_groups)-len(group)
            if available_spots > 0:
                for person in people:
                    if name in other_preferences[person] and person not in preferences[name]:
                        needed_spots += 1
                if available_spots == needed_spots:
                    best_group = group
                    break
                min_spots = available_spots
                if available_spots > needed_spots and available_spots < min_spots:
                    best_group = group
            else:
                continue
    return best_group

@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table, and give option to generate again"""
    # If user wants to generate again
    if request.method == "POST":
        num_groups = session.get('num_groups')
        names = session.get('names')
        preferences = session.get('preferences')
        dispreferences = session.get('dispreferences')
        groups = create_groups(names, preferences, dispreferences, num_groups)

        return render_template("groupings.html", groups=groups)
    else:
        return redirect("/")
