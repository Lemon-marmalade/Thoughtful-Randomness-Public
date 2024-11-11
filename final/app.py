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

@app.route("/")
def index():
    """ Obtain number of people user wishes to have grouped"""
    if request.method == "POST":
        people = request.form.get("people")
    # Ensure number was submitted
        if not people:
            return render_template("index.html")
        return render_template("input.html", people=people)

@app.route("/input", methods=["GET", "POST"])
def input():
    """Have a 2 column table for user to fill names into and select preferences with"""

    return render_template("input.html")

@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table"""

    return render_template("groupings.html")
