The flag is TMUCTF{r4nd0m_fl46_f0r_fun!_SzC!$JvnbrRh6kc*1@L!4vMueH1k0xKPJem@vh6Y2&Sb2CJzwjnTfU6wVZyePOK3}

Cythonized version benchmark is 6seconds:
-->Change challenge.py suffix to .pyx
-->Add a setup.py file as below:
import distutils.core
import Cython.Build
distutils.core.setup( ext_modules = Cython.Build.cythonize("challenge.pyx"))
-->Run This Command
python setup.py build_ext --inplace
-->Now run python interpreter and Run import challenge