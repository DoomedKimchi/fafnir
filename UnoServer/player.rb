require_relative 'card'
require_relative 'base_player'
class  PlayerA < BasePlayer
  
  def initialize
    super
    @@find_order = [:suit,:rank,:wild,:give_two]
  end

  def play_card  
    @@find_order.each do |kind|
      c = find(kind)
      if !c.nil?
        @hand.delete_if {|card| card == c}
        return c
      end
    end
    
    return nil
  end
end

class  PlayerB < BasePlayer
  def initialize
    super
    @@find_order = [:suit,:rank,:wild,:give_two]#[:give_two,:wild,:rank,:suit]
  end

  def play_card
    @@find_order.each do |kind|
      c = find(kind)
      if !c.nil?
        @hand.delete_if {|card| card == c}
        return c
      end
    end
    
    return nil
  end
end



