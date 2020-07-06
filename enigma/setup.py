from setuptools import setup
setup(
    name='enigma',
    version='0.1',
    py_modules=['enigma'],
    install_requires=[
        'Click',
    ],
    entry_points='''
    [console_scripts]
    enigma=enigma:cli
    ''',
)
