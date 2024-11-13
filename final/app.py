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
        name = int(request.form.get("people"))
        return render_template("groupings.html")
    else:
        return redirect("/")

@app.route("/groupings", methods=["GET", "POST"])
def groupings():
    """Display groupings in table, and give option to generate again"""
    if request.method == "POST":
        return render_template("groupings.html")
    else:
        return redirect("/")
