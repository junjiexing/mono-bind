
using System.Runtime.CompilerServices;

namespace TestLib
{
    public static class InteropTest
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string CFunc(string str, int i);

        public static string RegFuncTest(string str, int i)
        {
            return CFunc(str, i);
        }
    }
}
