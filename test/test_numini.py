import unittest

import param

class NumIniTest(unittest.TestCase):

    def test_normal(self):

        p = param.Parameters()
        p.read_config_file()

        self.assertEqual(p.width(), 11.)
        self.assertEqual(p.height(), 10.)
        self.assertEqual(p.position(), "bottom")
        #self.assertEqual(start,)

        expected_coords = {"x0": 2, "x1": 1, "y0": 5, "y1": -3.5}
        self.assertDictEqual(dict(p.coords()), expected_coords)
        self.assertEqual(list(p.properties()), [1,2,3])


if __name__ == '__main__':
    unittest.main()

