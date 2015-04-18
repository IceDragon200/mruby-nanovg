mruby-nanovg (WIP)
==================

Mruby Bindings for [nanovg](https://github.com/memononen/nanovg).

## mrb_config.rb
```ruby
MRuby::Build.new do |conf|
  #toolchain :gcc
  toolchain :clang # I used clang for testing, you can use gcc
  conf.gembox 'default'
  conf.gem github: 'IceDragon200/mruby-glfw3'
  conf.gem github: 'IceDragon200/mruby-nanovg'
  conf.gem github: 'take-cheeze/mruby-clang-plugin' # not required, just makes debugging nicer

  conf.cc do |cc|
    cc.include_paths << 'path/to/nanovg/src'
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

## Requirements:
```
mruby-glew
mruby-glfw3
```

## Docs
```shell
# to generate docs locally
rake docs
```

To `test` this binding you'll need [mruby-glfw3](https://github.com/IceDragon200/mruby-glfw3).

## TODO:
- [ ] Bind
  - [ ] Nanovg::Context.text_glyph_positions
  - [ ] Nanovg::Context.text_break_lines
  - [x] everything else
- [ ] Tests
  - [x] Nanovg
  - [x] Nanovg::Color
  - [ ] Nanovg::Context
  - [ ] Nanovg::Paint
  - [ ] Nanovg::Transform
- [ ] Samples / Examples
  - [ ] Port original nanovg ogl2 example
