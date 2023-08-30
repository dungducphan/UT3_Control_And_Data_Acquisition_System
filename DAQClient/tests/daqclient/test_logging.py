import unittest
from daqclient.logging import get_logger

class TestReadIMAQImage(unittest.TestCase):
    def test_get_acquire_logger(self):
        logger = get_logger('acquire')
        self.assertEqual(len(logger.handlers), 2)

if __name__ == '__main__':
    unittest.main()