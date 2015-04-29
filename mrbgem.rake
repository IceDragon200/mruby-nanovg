MRuby::Gem::Specification.new('mruby-nanovg') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '0.0.0'
  spec.summary = 'Nanovg bindings'
  spec.description = 'A Nanovg binding for mruby'
  spec.homepage = 'https://github.com/IceDragon200/mruby-nanovg'
  #spec.cc.flags << '-Werror'
  # We'll need some kind of OpenGL implementation
  add_dependency 'mruby-gles'
  add_dependency 'mruby-glew'
end
