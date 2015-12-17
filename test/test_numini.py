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

    def test_wrong_scalar_type(self):
        p = param.Parameters()
        msg = "In file <config/wrong_scalar_type.yaml>, " \
              "section <rectangle>, failed to read <width>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/wrong_scalar_type.yaml")

    def test_not_a_sequence(self):
        p = param.Parameters()
        msg = "In file <config/not_a_sequence.yaml>, " \
              "section <line>, failed to read <properties>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/not_a_sequence.yaml")

    def test_not_a_map(self):
        p = param.Parameters()
        msg = "In file <config/not_a_map.yaml>, section <line>, " \
              "failed to read <coords>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/not_a_map.yaml")

    def test_wrong_element_type_in_sequence(self):
        p = param.Parameters()
        msg = "In file <config/wrong_element_type_in_sequence.yaml>, " \
              "section <line>, failed to read <properties>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/wrong_element_type_in_sequence.yaml")

    def test_wrong_element_type_in_map(self):
        p = param.Parameters()
        msg = "In file <config/wrong_element_type_in_map.yaml>, " \
              "section <line>, failed to read <coords>."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/wrong_element_type_in_map.yaml")

    def test_object_wrong_scalar(self):
        p = param.Parameters()
        msg = "In file <config/wrong_element_type_in_object.yaml>, section " \
              "<rectangle>, failed to read <start> \(while processing: y\)."
        with self.assertRaisesRegexp(RuntimeError, msg):
            p.read_config_file("config/wrong_element_type_in_object.yaml")

    def test_vector_of_object(self):
        p = param.Parameters()
        p.read_config_file("config/vector_of_object.yaml", 1)
        expected_vstart= [ [0,1,2], [10,11,12], [20,21,22], ]
        vstart = [ [s.get_x(), s.get_y(), s.get_z()] for s in p.vstart()]
        self.assertEqual(vstart, expected_vstart)

    def test_map_of_object(self):
        p = param.Parameters()
        p.read_config_file("config/map_of_object.yaml", 2)
        expected_mstart= { "foo": [0,1,2], 
                           "bar": [10,11,12], 
                           "baz": [20,21,22], }
        mstart = {k:[v.get_x(), v.get_y(), v.get_z()]
                      for k,v in p.mstart().iteritems()}
        self.assertEqual(mstart, expected_mstart)

if __name__ == '__main__':
    unittest.main()
