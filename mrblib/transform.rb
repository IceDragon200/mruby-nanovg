module Nanovg
  class Transform
    # Translates the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Float] x
    # @param [Float] y
    # @return [Transform]
    def translate(x, y)
      dup.tap { |t| t.translate!(x, y) }
    end

    # Scales the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Float] x
    # @param [Float] y
    # @return [Transform]
    def scale(x, y)
      dup.tap { |t| t.scale!(x, y) }
    end

    # Rotates the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Float] angle
    # @return [Transform]
    def rotate(angle)
      dup.tap { |t| t.rotate!(angle) }
    end

    # Skews the transform horizontally and returns the result,
    # this does not affect the target transform.
    #
    # @param [Float] amount
    # @return [Transform]
    def skew_x(amount)
      dup.tap { |t| t.skew_x!(amount) }
    end

    # Skews the transform vertically and returns the result,
    # this does not affect the target transform.
    #
    # @param [Float] amount
    # @return [Transform]
    def skew_y(amount)
      dup.tap { |t| t.skew_y!(amount) }
    end

    # Multiplies the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Transform] trans
    # @return [Transform]
    def multiply(trans)
      dup.tap { |t| t.multiply!(trans) }
    end

    # Pre-Multiplies the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Transform] trans
    # @return [Transform]
    def pre_multiply(trans)
      dup.tap { |t| t.pre_multiply!(trans) }
    end

    # Inverses the transform and returns the result, this does not affect
    # the target transform.
    #
    # @param [Transform] trans
    # @return [Transform]
    def inverse(trans)
      dup.tap { |t| t.inverse!(trans) }
    end
  end
end
