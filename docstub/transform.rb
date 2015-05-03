module Nanovg
  # A 2x2 Transform
  class Transform
    # @!attribute a
    #   @return [Float]
    attr_accessor :a

    # @!attribute b
    #   @return [Float]
    attr_accessor :b

    # @!attribute c
    #   @return [Float]
    attr_accessor :c

    # @!attribute d
    #   @return [Float]
    attr_accessor :d

    # @!attribute e
    #   @return [Float]
    attr_accessor :e

    # @!attribute f
    #   @return [Float]
    attr_accessor :f

    # @param [Float] a
    # @param [Float] b
    # @param [Float] c
    # @param [Float] d
    # @param [Float] e
    # @param [Float] f
    # @return [self]
    def initialize(a = 0, b = 0, c = 0, d = 0, e = 0, f = 0)
    end

    # @param [Transform] other
    # @return [self]
    def initialize_copy(other)
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def translate!(x, y)
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def scale!(x, y)
    end

    # @param [Float] angle
    # @return [self]
    def rotate!(angle)
    end

    # @param [Float] amount
    # @return [self]
    def skew_x!(amount)
    end

    # @param [Float] amount
    # @return [self]
    def skew_y!(amount)
    end

    # @param [Transform] trans
    # @return [self]
    def multiply!(trans)
    end

    # @param [Transform] trans
    # @return [self]
    def pre_multiply!(trans)
    end

    # @param [Transform] trans
    # @return [Boolean] true if inverse was calculated, false otherwise
    def inverse!(trans)
    end
  end
end
