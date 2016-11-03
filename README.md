# nmrb
nmrb is mruby binding library for Microsoft .NET framework 4.6.

About mruby: https://github.com/mruby/mruby/blob/master/README.md

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

### Required

* Microsoft Windows 7 or later
* Microsoft Visual Studio 2015
* Ruby (for build mruby)
* Git

### Process

    git clone git@github.com:dyama/nmrb.git
    cd nmrb
    git clone git@github.com:mruby/mruby.git
    cd mruby
    ruby minirake
    cd ..
    devenv.exe nmrb.sln

## License

MIT License

## Author

dyama (Daisuke YAMAGUCHI) dyama@member.fsf.org

    
