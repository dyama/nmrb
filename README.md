# nmrb
nmrb is mruby binding library for Microsoft .NET framework 4.6.

About mruby: https://github.com/mruby/mruby/blob/master/README.md

![nmrb](http://dyama.org/wp-content/uploads/2016/11/nmrb.png)

## Examples

    // Make MrbState object.
    using (var mrb = new nmrb.State()) {
    
       // Ruby script
       var src = @"
         def hello(n)
           puts 'hello!' * n
         end
         # call the method
         hello 3
       ";
       // Execute
       mrb.Do(src);
    
       // Returns value
       Value value = mrb.Do("123");
       int result = (value as FixnumValue).ToInteger();
       
       // Callback C# function from Ruby environment
       mrb.DefineCliMethod("clifunc", (args) => {
         if (args.Length > 0 && args.First().IsString()) {
           string message = args.First().ToString();
           var button = MessageBox.Show(message, "mruby", MessageBoxButtons.OKCancel);
           if (button == DialogResult.OK) {
             return new TrueValue(mrb);
           }
           return new FalseValue(mrb);
         }
         return new NilValue(mrb);
       });
       mrb.Do("clifunc 'こんにちは、世界。'");
       
    }

## Target platform

* IA32 compatible 32bit processor.
* Win32
* Microsoft .NET Framework 4.6.1 (No tested with .NET Core)

## How to call from C# app

1. Add Reference DLL file named nmrb.dll to your C# project.
2. Add following line to source code.

    using nmrb;
    
3. Make `MrbState` object.

    var mrb = new MrbState();
    
4. Call `Do` function with Ruby script string.

    mrb.Do("puts 'happy mruby life!'");
    
## How to build nmrb.dll

Requirements

* Microsoft Windows 7 or later
* Microsoft Visual Studio 2015
* Ruby (for build mruby)
* Git

Process

    git clone --recursive git@github.com:dyama/nmrb.git
    cd nmrb/mruby
    ruby minirake
    cd ..
    devenv.exe nmrb.sln

## Note

* Callback mapper object is *static*. It means that do not guarantee independence between multiple nmrb.State objects.
* DefineCliMethod supports to add a method to Kernel module only.

## License

MIT License

## Author

dyama (Daisuke YAMAGUCHI) dyama@member.fsf.org

    
