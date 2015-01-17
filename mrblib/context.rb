module Nanovg
  class Context
    class AbortFrame < IndexError
    end

    alias :initialize_w_flags :initialize
    def initialize(*args)
      if args.empty?
        initialize_w_flags(0)
      else
        initialize_w_flags(*args)
      end
    end

    def abort_frame
      cancel_frame
      raise AbortFrame
    end

    def draw(*args)
      begin_frame(*args)
      yield self
      end_frame
    rescue AbortFrame
      nil
    end
  end
end
