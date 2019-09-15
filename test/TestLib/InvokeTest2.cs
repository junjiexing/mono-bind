using System;

namespace TestLib
{
    public class InvokeTest2
    {
        public long CubicSum(long a, long b, long c)
        {
            return a * a * a + b * b * b + c * c *c;
        }

        public string StrCat(string a, string b)
        {
            return a + b;
        }

        public void OutTest(out int a)
        {
            a = 42;
        }

        public void RefTest(ref int a)
        {
            a += 1;
        }

        public string StructTest(TestStruct1 st)
        {
            return $"{st.s}{st.a}{st.b}";
        }
    }
}
