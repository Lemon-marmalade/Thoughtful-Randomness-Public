import secrets

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from random import shuffle
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
        people = session.get('people')
        # Get names and add to array
        for i in range(people):
            name = request.form.get(f"name{i}")
            if name:
                names.append(name)
                preferences[name] = request.form.getlist(f"preferences{i}")
        # Save info to session
        session['names'] = names
        session['preferences'] = preferences
        # Do some group creating magic
        groups = create_groups(names, preferences, num_groups)

        return render_template("groupings.html", groups=groups)

    else:
        return redirect("/")

def create_groups(names, preferences, num_groups):
    groups = [[] for _ in range(num_groups)]
    names = list
    sorted_names = sorted(names, key=lambda name: len(preferences[name]), reverse=True)
    for name in sorted_names:
        best_group = find_best(name, groups, preferences[name], preferences)
        best_group.append(name)
    return groups

def find_best(name, groups, preferences, other_preferences):
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
    return best_group

@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table, and give option to generate again"""
    # If user wants to generate again
    if request.method == "POST":
        num_groups = session.get('num_groups')
        names = session.get('names')
        preferences = session.get('preferences')
        groups = create_groups(names, preferences, num_groups)

        return render_template("groupings.html", groups=groups)
    else:
        return redirect("/")
