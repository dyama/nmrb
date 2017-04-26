using System;
using System.Linq;
using System.Windows.Forms;
using nmrb;
using static System.Console;

namespace nmrb_test
{
  class Program
  {
    [STAThread]
    static void Main()
    {
      using (var mrb = new State()) {

        // mrb.DefineCliMethod("hoge", (args) => {
        //   throw new Exception("foobarbaz");
        //   return new NilValue();
        // });
        // var oo = mrb.Do("hoge");
        // var ooo = oo.ToString(mrb);

        mrb.Do("c=123");

        WriteLine(mrb["'test'"].ToString(mrb));
        WriteLine(mrb["c = 123; c+=1"].ToString(mrb));

        mrb.Do(@"
        class Test
          def hello
            puts 'hello, mruby!'
          end
        end
        ");
        mrb.Do("Test.new.hello");

        // Array to Array
        dynamic ary = mrb["[1, 'X', :sym, 3.14]"];
        foreach (var a in ary.ToArray(mrb)) {
          WriteLine(a.ToString(mrb));
        }
        ary = mrb["'mruby'.each_char.to_a"];
        foreach (var a in ary.ToArray(mrb)) {
          WriteLine(a.ToString(mrb));
        }

        // Hash to Dictionary
        foreach (var a in mrb["{foo:'ほげ', bar:'ふが'}"].ToDictionary(mrb)) {
          WriteLine($"({a.Key.ToString(mrb)}, {a.Value.ToString(mrb)})");
        }

        // Define C# function to ruby env
        mrb.DefineCliMethod("csfunc", (args) => {
          if (args.Length > 0) {
            var ss = (args[0] as StringValue).ToString(mrb);
            MessageBox.Show(ss);
          }
          return new NilValue();
        });

        // Call C# function from ruby
        mrb.Do("csfunc 'こんにちは！' * 3");

        // funcall
        mrb.Do(@"
        def twice(x)
          x * x
        end
        ");
        dynamic res = mrb.FunCall("twice", new FixnumValue(5));
        var ans = res.ToInteger();

        WriteLine($"ans: {ans}");

        ReadLine();
      }

    }
  }
}
