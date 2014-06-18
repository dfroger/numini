import unittest

import param

class NumIniTest(unittest.TestCase):

    def test_normal(self):

        p = param.Parameters()
        p.read_config_file("config.yaml")

        self.assertEqual(p.width(), 11.)
        self.assertEqual(p.height(), 10.)
        self.assertEqual(p.position(), "bottom")
        self.assertEqual(p.start().get_x(), 1)
        self.assertEqual(p.start().get_y(), 3)
        self.assertEqual(p.start().get_z(), 0)

        expected_coords = {"x0": 2, "x1": 1, "y0": 5, "y1": -3.5}
        self.assertDictEqual(dict(p.coords()), expected_coords)
        self.assertEqual(list(p.properties()), [1,2,3])

    def test_unknown_section(self):

        p = param.Parameters()
        msg = "In file <config_unknown_section.yaml>, unknown section: <foo>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config_unknown_section.yaml")


if __name__ == '__main__':
    unittest.main()

