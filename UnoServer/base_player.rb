require_relative 'deck'
class BasePlayer
  def initialize
    @hand = []
    @game_state = {}
  end
  def update_game_state(state = {:top_card=>Card.new(1,:spades), :other_cards=>[7],
     :skip=>false, :direction => :c})
    @game_state = state.clone
  end
  
  def to_s
    raise NotImplementedError.new("You must implement this")
  end
  
  def add_card card
    @hand=[] if @hand.nil?
    @hand.push(card)
  end
  
  def give_hand cards#adds 7 cards to hand, erases previous hand
    @hand = cards.clone
  end
  
  def play_card
    raise NotImplementedError.new("You must implement this")
    #play a card based off hand and gameState
    #needs to request a card from the game server if he's out
    #meat of the program
  end
  
  def win?
    @hand.empty?
  end
  
  def find (kind)   
    case kind
    when :rank
      return @hand.find {|card| card.rank==@game_state[:top_card].rank}
    when :suit
      return @hand.find {|card| card.suit==@game_state[:top_card].suit}
    when :wild
      return @hand.find {|card| card.wild?}
    when :give_two
      return @hand.find {|card| card.give_two?}
    else
      raise "invalid kind of search"
    end
  end
  
  def to_s
    "(#{@hand.size}) #{@hand.join(", ")}\n"
  end
end