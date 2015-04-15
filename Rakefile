require 'yard'
require 'yard/rake/yardoc_task'

YARD::Rake::YardocTask.new do |t|
  t.files = ['docstub/**/*.rb', 'mrblib/**/*.rb']
end

task docs: :yard
task default: [:docs]
