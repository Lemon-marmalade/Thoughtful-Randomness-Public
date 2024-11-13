import os

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
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
        return render_template("input.html", people=people)
    else:
        return render_template("index.html")

@app.route("/input", methods=["GET", "POST"])
def input():
    """Use the info from the table to generate random groups"""
    if request.method == "POST":
        # Extract number of groups
        num_groups = int(request.form.get("groups"))
        # Create empty array and empty dictionary for names and preferences
        names = []
        preferences = {}
        people = int(request.form.get("people"))
        # Get names and add to array
        for i in range(people):
            name = request.form.get(f"name{i}")
            if name:
                names.append(name)
                preferences[name] = request.form.getlist(f"preferences{i}")

        # Do some group creating magic
        groups = create_groups(names, preferences, num_groups)

        return render_template("groupings.html", groups=groups)

    else:
        return redirect("/")



@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table, and give option to generate again"""
    if request.method == "POST":
        return render_template("groupings.html")
    else:
        return redirect("/")
