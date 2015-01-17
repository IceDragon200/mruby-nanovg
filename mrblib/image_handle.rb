module Nanovg
  class ImageHandle
    attr_reader :context
    attr_reader :image

    def initialize(context, image)
      @context = context
      @image = image
    end

    def sizes
      @context.image_size(@image)
    end

    def delete
      @context.delete_image(@image)
    end

    def update(*args)
      @context.update_image(@image, *args)
    end

    def to_int
      @image
    end

    def to_i
      @image
    end
  end
end
