#!/bin/bash
#Daniel Joy, drjoy@cn.edu, 0587254

paths=( "Documents" "Downloads" "Pictures" "Documents/test_folder" "c_prog" )
for x in "${paths[@]}"
do
	cd
	cd $x
	if [ -f flag.txt ]
	then
		rm flag.txt
	fi
done

randomVar=$(($RANDOM % 5))


if [ -f highscore.txt ]
then
	for data in `cat highscore.txt`
	do
		highscore=$data
	done
fi

echo "Current Highscore: $highscore seconds"
case $randomVar in
	0) echo > /home/dan/Documents/flag.txt ;;
	1) echo > /home/dan/Downloads/flag.txt ;;
	2) echo > /home/dan/Pictures/flag.txt ;;
	3) echo > /home/dan/Documents/test_folder/flag.txt ;;
	4) echo > /home/dan/c_prog/flag.txt ;;
	esac

echo "Welcome to Find the Flag!"
echo "The goal is to find the flag in the quickest time possible."
echo ""
echo "The flag will be hidden in one of the folders inside the home directory."
echo "(You will need to open a second terminal to find it. no using the file manager!"
echo "Once you have found it, type in the folder name (NOT PATH) into here:"
echo "Good luck!"


start=$SECONDS
read -p "flag.txt is hidden inside: " answer

function wrong() {
	echo "Sorry, that was not the correct folder."
	echo "Thank you for playing!"
	exit 0
}

function right() {
	echo "That was the correct folder! Great job!"
	score=$(( $SECONDS - start ))
	echo "You found the flag in $score seconds!"
	if (( $score < $highscore ))
	then
		rm highscore.txt
		touch highscore.txt
		echo $score >> highscore.txt
		echo "You got a new high score of $score seconds!"
	else
		echo "Unfortunately, you did not beat your previous score of $highscore seconds."
	fi
	echo "Thank you for playing!"
	exit 0
}

echo $answer
case $randomVar in
	0)
	echo "Case 0"
	if [ $answer = "Documents" -o $answer = "documents" ]
	then
		right
	else
		wrong
	fi ;;
	1)
	echo "Case 1"
	if [ $answer = "Downloads" -o $answer = "downloads" ]
	then
		right
	else
		wrong
	fi ;;
	2)
	echo "Case 2"
	if [ $answer = "Pictures" -o $answer = "pictures" ]
	then
		right
	else
		wrong
	fi ;;
	3)
	echo "Case 3"
	if [ $answer = "test_folder" -o $answer = "Test_folder" ]
	then
		right
	else
		wrong
	fi ;;
	4)
	echo "Case 4"
	if [ $answer = "c_prog" -o $answer = "C_prog" ]
	then
		right
	else
		wrong
	fi ;;
	esac


