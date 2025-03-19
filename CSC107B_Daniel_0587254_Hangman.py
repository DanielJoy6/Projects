# Course: CSC107B
# Name: Daniel Joy
# ID: 0587254
# Email: drjoy@cn.edu

import random
import turtle
import time

#TODO: Print alphabet, turn from gray to red/green when guessed
#Multiplayer vs singleplayer mode

sentenceCharacters = []
correctGuesses = 0
sentenceLength = 0
alreadyGuessed = []
numWrongGuesses = 0
wrongGuesses = []
keepGoing = True
def wait(n): #basic function for waiting
    time.sleep(n)
def draw_gallows(): #draws gallows
    turtle.color("white")
    turtle.width(8)
    turtle.up()
    turtle.goto(-200, 100)
    turtle.down()
    turtle.forward(100)
    turtle.backward(50)
    turtle.left(90)
    turtle.forward(150)
    turtle.left(90)
    turtle.forward(80)
    turtle.left(90)
    turtle.forward(30)
    #print(turtle.pos())

def add_body_part():
    turtle.color("white")
    turtle.width(5)
    global numWrongGuesses
    if(numWrongGuesses == 1):
        turtle.goto(-230, 180)
        turtle.down()
        turtle.circle(15)
    elif(numWrongGuesses == 2):
        turtle.goto(-230, 180)
        turtle.down()
        turtle.setheading(270)
        turtle.forward(35)
    elif(numWrongGuesses == 3):
        turtle.goto(-230, 175)
        turtle.setheading(315)
        turtle.down()
        turtle.forward(30)
    elif(numWrongGuesses == 4):
        turtle.goto(-230, 175)
        turtle.setheading(225)
        turtle.down()
        turtle.forward(30)
    elif(numWrongGuesses == 5):
        turtle.goto(-230, 142)
        turtle.setheading(315)
        turtle.down()
        turtle.forward(30)
    elif(numWrongGuesses == 6):
        turtle.goto(-230, 142)
        turtle.setheading(225)
        turtle.down()
        turtle.forward(30)
    turtle.up()
    turtle.goto(-250, 0)
    turtle.setheading(0)

def get_random_sentence(): #generates a random sentence
    names = []
    middles = []
    places = []
    names_file = open('Names.txt', 'r')
    for line in names_file:
        temp = line.strip("\n")
        names.append(temp)
    middles_file = open('Middle.txt', 'r')
    for line in middles_file:
        temp = line.strip("\n")
        middles.append(temp)
    places_file = open('Places.txt', 'r')
    for line in places_file:
        temp = line.strip("\n")
        places.append(temp)
    sentence = "" + random.choice(names) + " " + random.choice(middles) + " " + random.choice(places) + "."
    return sentence
def draw_spaces(str): #drawing spaces for generated sentence
    turtle.speed(2)
    global sentenceCharacters
    sentenceCharacters = str.split(" ")
    global sentenceLength
    for x in sentenceCharacters:
        sentenceLength += len(x)
    totalchar = 0
    turtle.goto(-250, 0)
    turtle.setheading(0)
    for x in sentenceCharacters:
        #print(len(x), totalchar)
        if(totalchar + len(x) > 20):
            turtle.goto(-250, turtle.ycor() - 40)
            totalchar = 0
        totalchar += len(x)
        for char in x:
            if(char == x[-1] and x == sentenceCharacters[-1]):
                turtle.write(".", font=("Arial", 20, "normal"))
            else:
                turtle.write("_", font=("Arial", 20, "normal"))
            turtle.forward(20)
        turtle.forward(20)

def main_loop(): #Guessings letters / logic
    charToGuess = input("Guess a letter: ")
    global alreadyGuessed, wrongGuesses, numWrongGuesses, correctGuesses, sentenceCharacters
    if(charToGuess in alreadyGuessed or charToGuess in wrongGuesses):
        charToGuess = input("You've already guessed this letter! Guess a new one: ")
    while len(charToGuess) < 1:
        charToGuess = input("Guess an actual letter: ")
    charToGuess = charToGuess[0]
    badcharacters = ["[", "]", ",", ".", "/", "?", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
    if charToGuess not in badcharacters:
        charToGuess = charToGuess.lower()
        turtle.goto(-250, 0)
        guessIsRight = False
        totalchar = 0
        for x in sentenceCharacters:
            if(totalchar + len(x) > 20):
                turtle.goto(-250, turtle.ycor() - 40)
                totalchar = 0
            totalchar += len(x)
            for char in x:
                if(charToGuess == char or charToGuess.upper() == char):
                    guessIsRight = True
                    correctGuesses += 1
                    #print(correctGuesses, sentenceLength)
                    if charToGuess not in alreadyGuessed:
                        alreadyGuessed.append(charToGuess)
                    turtle.goto(turtle.xcor(), turtle.ycor() + 10)
                    turtle.write(charToGuess, font=("Arial", 20, "normal"))
                    turtle.goto(turtle.xcor(), turtle.ycor() - 10)
                turtle.forward(20)
            turtle.forward(20)
        if not guessIsRight:
            turtle.goto(-80, -200)
            numWrongGuesses += 1
            for x in range(numWrongGuesses):
                turtle.forward(23)
            turtle.write(charToGuess, font=("Arial", 20, "normal"))
            add_body_part()
            wrongGuesses.append(charToGuess)
        else:
            turtle.goto(-80, -150)
            turtle.forward(23 * len(alreadyGuessed))
            turtle.write(charToGuess, font=("Arial", 20, "normal"))


def run_intro():
    turtle.setup(800, 600)
    turtle.title("Hangman by Dan")
    turtle.speed(5)
    turtle.color("white")
    turtle.bgcolor("black")
    turtle.up()
    turtle.goto(-100, 200)
    turtle.write("Welcome To",font=("Arial", 50, "normal"))
    turtle.goto(-100, 100)
    turtle.write("Hangman!",font=("Arial", 50, "normal"))
    wait(1)
    second_part_of_intro()
def second_part_of_intro():
    global sentenceLength, sentenceCharacters, correctGuesses, alreadyGuessed, wrongGuesses, numWrongGuesses, keepGoing
    turtle.clear()
    draw_gallows()
    turtle.up()
    turtle.goto(-300, -200)
    turtle.write("Wrong Characters:",font=("Arial", 20, "normal"))
    turtle.goto(-300, -150)
    turtle.write("Correct Characters:", font=("Arial", 20, "normal"))
    sentence = get_random_sentence()
    draw_spaces(sentence)
    while numWrongGuesses < 6 and correctGuesses < sentenceLength - 1:
        main_loop()
    turtle.clear()
    turtle.goto(-170, 0)
    turtle.down()
    turtle.color("white")
    if(numWrongGuesses == 6):
        turtle.write("GAME OVER", font=("Arial", 80, "normal"))
    elif(correctGuesses == sentenceLength - 1):
        turtle.write("Congratulations!", font=("Arial", 60, "normal"))
        turtle.up()
        turtle.goto(turtle.xcor(), turtle.ycor() - 60)
        turtle.down()
        turtle.write("You win!!", font=("Arial", 60, "normal"))
    play_again = input("Would you like to play again?")
    if(play_again.lower() == "yes" or play_again.lower() == "y"):
        sentenceCharacters = []
        correctGuesses = 0
        sentenceLength = 0
        alreadyGuessed = []
        numWrongGuesses = 0
        wrongGuesses = []
        keepGoing = True
        second_part_of_intro()
    else:
        turtle.exitonclick()
run_intro()

turtle.exitonclick()
