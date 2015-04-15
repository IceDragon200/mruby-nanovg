module Nanovg
  # An ImageHandle is a helper class for managing images from a context
  # its a simple ruby implementation so it should be garbage collected safely.
  # Don't try throwing random numbers in it to get a image though,
  # this does absolutely no checks to ensure validity of the provided image id.
  class ImageHandle
    # @!attribute [r] context
    #   @return [Context]
    attr_reader :context
    # @!attribute [r] image
    #   @return [Integer]
    attr_reader :image

    # @param [Context] context
    # @param [Integer] image
    def initialize(context, image)
      @context = context
      @image = image
    end

    # Returns the dimensions of the image
    #
    # @return [Array<Float>]
    def dimensions
      @context.image_size(@image)
    end

    # Deletes the image
    #
    # @return [void]
    def delete
      @context.delete_image(@image)
    end

    # Updates the image.
    #
    # see {Context#update_image}
    # @return [void]
    def update(*args)
      @context.update_image(@image, *args)
    end

    # Returns the image handle
    alias :to_int :image
    # Returns the image handle
    alias :to_i :image
  end
end
