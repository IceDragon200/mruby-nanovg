mruby-nanovg (WIP)
==================

Mruby Bindings for [nanovg](https://github.com/memononen/nanovg).

mruby_build_config.rb
```ruby
MRuby::Build.new do |conf|
  #toolchain :gcc
  toolchain :clang # I used clang for testing, you can use gcc
  conf.gembox 'default'
  conf.gem github: 'take-cheeze/mruby-glfw3'   # its also a dependency so don't worry too much, (which should change later)
  conf.gem github: 'IceDragon200/mruby-nanovg'
  conf.gem github: 'take-cheeze/mruby-clang-plugin' # not required, just makes debugging nicer

  conf.cc do |cc|
    cc.include_paths << 'path/to/nanovg/src'
  end

  conf.cxx do |cxx|
    cxx.flags << '-std=c++11' # required for mruby-glfw3 (until someone backports it to C)
  end

  conf.linker do |linker|
    linker.library_paths << 'path/to/nanovg/build'
    linker.libraries << 'GL'     # for mruby-nanovg and glfw
    linker.libraries << 'GLEW'   # for mruby-nanovg
    linker.libraries << 'glfw'   # for mruby-glfw3
    linker.libraries << 'nanovg' # for mruby-nanovg
  end
end
```

Requirements:
```
GLEW
```

To `test` this binding you'll need [mruby-glfw3](https://github.com/take-cheeze/mruby-glfw3).
