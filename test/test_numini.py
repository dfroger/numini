import unittest

import param

class NumIniTest(unittest.TestCase):

    def test_normal(self):

        p = param.Parameters()
        p.read_config_file("config/normal.yaml")

        self.assertEqual(p.width(), 11.)
        self.assertEqual(p.height(), 10.)
        self.assertEqual(p.position(), "bottom")
        self.assertEqual(p.start().get_x(), 1)
        self.assertEqual(p.start().get_y(), 3)
        self.assertEqual(p.start().get_z(), 0)

        expected_coords = {"x0": 2, "x1": 1, "y0": 5, "y1": -3.5}
        self.assertDictEqual(dict(p.coords()), expected_coords)
        self.assertEqual(list(p.properties()), [1,2,3])

    def test_file_existance(self):

        p = param.Parameters()
        msg = " Can not open file <config/nosuch.yaml> for reading."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/nosuch.yaml")

    def test_unknown_section(self):

        p = param.Parameters()
        msg = "In file <config/unknown_section.yaml>, unknown section: <foo>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/unknown_section.yaml")

    def test_unknown_key(self):
        p = param.Parameters()
        msg = "In file <config/unknown_key.yaml>, " \
              "section: <rectangle>, unknown key: <foo>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/unknown_key.yaml")

    #def test_wrong_scalar_type(self):
        #p = param.Parameters()
        #msg = "In file <config/wrong_scalar_type.yaml>, " \
              #"section <rectangle>, failed to read <width>: " \
              #"expected a type: d, but got value: <foo>."
        #with self.assertRaisesRegexp(RuntimeError, msg):
            #p.read_config_file("config/wrong_scalar_type.yaml")

    #def test_not_a_sequence(self):
        #p = param.Parameters()
        #msg = "In file <config/not_a_sequence.yaml>, " \
              #"section <line>, failed to read <properties>: " \
              #"expected a type: vector<i>, but got non sequence value: <0>."
        #with self.assertRaisesRegexp(RuntimeError, msg):
            #p.read_config_file("config/not_a_sequence.yaml")

    #def test_not_a_map(self):
        #p = param.Parameters()
        #msg = "In file <config/not_a_map.yaml>, section <line>, " \
              #"failed to read <coords>: expected a type: " \
              #"map<Ss,d>, but got non map value: <1.>."
        #with self.assertRaisesRegexp(RuntimeError, msg):
            #p.read_config_file("config/not_a_map.yaml")

    #def test_wrong_element_type_in_sequence(self):
        #p = param.Parameters()
        #msg = "In file <config/wrong_element_type_in_sequence.yaml>, " \
              #"section <line>, failed to read on element of <properties>: " \
              #"expected a type: vector<i>, but got value: <- foo>."
        #with self.assertRaisesRegexp(RuntimeError, msg):
            #p.read_config_file("config/wrong_element_type_in_sequence.yaml")

    #def test_wrong_element_type_in_map(self):
        #p = param.Parameters()
        #msg = "In file <config/wrong_element_type_in_map.yaml>, " \
              #"section <line>, failed to read on element of <coords>: " \
              #"expected a type: map<d>, but got value: <!<!> x0: foo>."
        #with self.assertRaisesRegexp(RuntimeError, msg):
            #p.read_config_file("config/wrong_element_type_in_map.yaml")

if __name__ == '__main__':
    unittest.main()
