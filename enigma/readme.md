# Enigma Simulartor

First run the `todays_rotor_generator.py` and it will produce a rotor configuration saved in `todays_rotor_state.enigma` file.


### Run
1. Run from python:
	- Run `enigma.py` with `-m` or `--message` switch
	```
	python enigma.py -m 'message'
	 ```
	- Run `enigma.py` without switch and give your message inside the program
	```
	python enigma.py
	```
1. Run from setuptools:
Init requirements by runnig:
```
virtualenv venv
source venv/bin/activate
pip install --editable . # OR
pip install -e .
```
and then run `enigma` instead of `python enigma.py`


