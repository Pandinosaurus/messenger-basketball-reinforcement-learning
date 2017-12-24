# Messenger-basketball-reinforcement-learning
Using reinforcement learning to play basketball messenger with a robotic arm.

This project is based on: https://github.com/JoshuaRiddell/messenger-basketball-player

## Requirments
* ```Python 2.7```
* ```OpenCV```
* ```numpy```
* ```Pillow```
* ```pytesseract```

## Modules

The project is based on 3 modules:
1. The computer vision (folder ```cv```) module that processes the video stream and extracts information from it. This information will be the input of the learning module.
2. The learning module (folder ```learning```), that takes the data extracted from the cv module as input and outputs the chosen action.
3. The inverse kinematics module (folder ```ik```), that takes an action as input and, via the inverse kinematics of the arm, computes the servo signals required to perform that action.

The way in which the modules relate to each other is illustrated below:

![relations](https://github.com/juangallostra/messenger-basketball-reinforcement-learning/blob/develop/resources/module_diagram.png)

### CV module

![cv](https://github.com/juangallostra/messenger-basketball-reinforcement-learning/blob/develop/resources/cv_grid.gif)

### Learning module

### IK module

