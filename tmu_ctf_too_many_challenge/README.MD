The flag is `TMUCTF{r4nd0m_fl46_f0r_fun!_SzC!$JvnbrRh6kc*1@L!4vMueH1k0xKPJem@vh6Y2&Sb2CJzwjnTfU6wVZyePOK3}`

Cythonized version benchmark is  6seconds
## How To Test It?
- Change challenge.py suffix to .pyx
- Add a setup.py file as below:
- `import distutils.core`
- `import Cython.Build`
- `distutils.core.setup(
    ext_modules = Cython.Build.cythonize("challenge.pyx"))`
- And then run This Command Below:
- `python setup.py build_ext --inplace`<br>
<br>**All files till here are included in my fork/cython folder
- Now you just need to run python interpreter and Run `import challenge`

