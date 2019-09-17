using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestLib
{
    public class Field
    {
        public int a;
    }

    public class GetterSetterTest
    {
        private int _a;
        private string _b;
        public int A { get { return _a + 1; } set { _a = value + 1; } }
        public string B { get { return _b; } set { _b = value; } }

        private Field _field;
        public Field F { get; set; }
    }
}
