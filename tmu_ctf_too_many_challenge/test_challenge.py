import unittest
from timeit import timeit

from challenge import func


class TestChallenge(unittest.TestCase):
    def test_one_speed(self):
        time_of_one_number_solve = timeit(lambda: func(751741232), number=5)/5
        self.assertGreater(1, time_of_one_number_solve,
                           f'To slow {time_of_one_number_solve:.2f} seconds for iter!')


if __name__ == '__main__':
    unittest.main()
