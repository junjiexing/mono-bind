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
    }
}
