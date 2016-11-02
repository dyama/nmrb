using System;
using System.Linq;
using System.Windows.Forms;
using nmrb;
using static System.Console;

namespace nmrb_test
{
  class Program
  {
    static void Main()
    {
      using (var mrb = new MrbState()) {

        mrb.Do("c=123");

        WriteLine(mrb["'test'"]);
        WriteLine(mrb["c = 123; c+=1"]);

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
        foreach (var a in ary.ToArray()) {
          WriteLine(a);
        }
        ary = mrb["'mruby'.each_char.to_a"];
        foreach (var a in ary.ToArray()) {
          WriteLine(a);
        }

        // Hash to Dictionary
        foreach (var a in mrb["{foo:'hoge', bar:'fuga'}"].ToDictionary()) {
          WriteLine(a);
        }

        // Define C# function to ruby env
        mrb.DefineCliMethod("csfunc", (args)=> {
          if (args.Length > 0 && args[0].IsFixnum()) {
            int n = (args[0] as MrbFixnumValue).ToInteger();
            for (int i = 0; i < n; i++) {
              WriteLine("callback");
            }
          }
          else {
            WriteLine("callback");
          }
          MessageBox.Show("hello!");
          return new MrbStringValue(mrb, "This is C#.");
        });

        // Call C# function from ruby
        mrb.Do("p csfunc(3)");

        // funcall
        mrb.Do(@"
        def twice(x)
          x * x
        end
        ");
        dynamic res = mrb.FunCall("twice", new MrbFixnumValue(mrb, 5));
        var ans = res.ToInteger();

        WriteLine($"ans: {ans}");

        ReadLine();
      }

    }
  }
}
