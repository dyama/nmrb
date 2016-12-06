using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using nmrb;

namespace nmrb_unittest
{
  [TestClass]
  public class UnitTest1
  {
    [TestMethod]
    public void Test1()
    {
      State mrb = new State();
      mrb.Dispose();
      mrb = null;
    }

    [TestMethod]
    public void Test2()
    {
      using (var mrb = new State()) {
        Assert.AreEqual(new FixnumValue(123).ToInt32(), 123);
        Assert.AreEqual(new FloatValue(mrb, 3.14).ToDouble(), 3.14);
        Assert.AreEqual(new TrueValue().ToBoolean(), true);
        Assert.AreEqual(new FalseValue().ToBoolean(), false);
        Assert.AreEqual(new StringValue(mrb, "foobarbaz").ToString(mrb), "foobarbaz");
        Assert.AreEqual(new SymbolValue(mrb, "hogefuga").ToString(mrb), "hogefuga");
      }
    }

    [TestMethod]
    public void Test3()
    {
      using (var mrb = new State()) {
        dynamic r = mrb["123"];
        //mrb.Do("true");
        // // Assert.AreEqual(t, nmrb.ValueType.TRUEVAL);
        //Assert.AreEqual(mrb.Do("false").ToBoolean(), false);
      }
    }

    [TestMethod]
    [Ignore]
    public void Unicodecheck()
    {
      //Assert.AreEqual(new StringValue(mrb, "こんにちは").ToString(mrb), "こんにちは");
    }

  }
}
