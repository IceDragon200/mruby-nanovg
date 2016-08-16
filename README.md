mruby-nanovg (WIP)
==================

Mruby Bindings for [nanovg](https://github.com/memononen/nanovg).

## mrb_config.rb
```ruby
MRuby::Build.new do |conf|
  #toolchain :gcc
  toolchain :clang # I used clang for testing, you can use gcc

  conf.gembox 'default'
  conf.gem github: 'IceDragon200/mruby-glew'
  conf.gem github: 'IceDragon200/mruby-glfw3'
  conf.gem github: 'IceDragon200/mruby-nanovg'
  conf.gem github: 'take-cheeze/mruby-clang-plugin' # not required, just makes debugging nicer

  conf.cc do |cc|
    cc.include_paths << 'path/to/nanovg/src'
  end

  conf.linker do |linker|
    linker.library_paths << 'path/to/nanovg/build'
    linker.libraries << 'GL'     # for mruby-nanovg and glfw
    linker.libraries << 'GLEW'   # for mruby-glew
    linker.libraries << 'glfw'   # for mruby-glfw3
    linker.libraries << 'nanovg' # for mruby-nanovg
  end
end
```

## Requirements:
In order to build and use the gem, the following gems are required

* [mruby-idextmacros](https://github.com/IceDragon200/mruby-idextmacros)
  Include this in your build_config include path, it has helper macros used by the gem for creating attribute fields and generic methods
* [mruby-glew](http://github.com/IceDragon200/mruby-glew)
* [mruby-gles](http://github.com/take-cheeze/mruby-gles)

If you wish to try the examples, you'll need [mruby-glfw3](https://github.com/IceDragon200/mruby-glfw3)

## Defines
| Name                 | Description                       |
| -------------------- | --------------------------------- |
| `MRUBY_NANOVG_GL2`   | Uses `NANOVG_GL2_IMPLMENTATION`   |
| `MRUBY_NANOVG_GL3`   | Uses `NANOVG_GL3_IMPLMENTATION`   |
| `MRUBY_NANOVG_GLES2` | Uses `NANOVG_GLES2_IMPLMENTATION` |
| `MRUBY_NANOVG_GLES3` | Uses `NANOVG_GLES3_IMPLMENTATION` |

## Docs
```shell
# to generate docs locally, you'll need c-ruby, rake and yard installed.
rake docs
```

## Gotchas
```ruby
# text_break_lines is a tricky function to wrap, instead I've opted to handle the row buffering intenrally and yield the params back to the user
context.text_break_lines text, width do |row_string, row_width, min_x, max_x|
  # do stuff with the row_string
end

context.text_glyph_positions(x, y, text) #=> [[x, min_x, max_x]...]
```
## TODO:
- [ ] Bind
  - [x] Nanovg::Context.text_glyph_positions
  - [x] Nanovg::Context.text_break_lines
  - [x] everything else
- [ ] Tests
  - [x] Nanovg
  - [x] Nanovg::Color
  - [ ] Nanovg::Context
  - [ ] Nanovg::Paint
  - [ ] Nanovg::Transform
- [ ] Samples / Examples
  - [ ] Port original nanovg ogl2 example
