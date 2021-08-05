# Enigma Simulartor

First run the `todays_rotor_generator.py` or run the app with `-r` or `restart` to produce a rotor configuration saved in `todays_rotor_state.enigma` file.


Then run `python enigma_code_decode.py` and enter the message or run the app with `-m` or `--message` option.
``` Shell
$ python enigma_code_decode.py
Message: Hello
# encoded message

$ python enigma_code_decode.py -m Hello
# encoded message
```

