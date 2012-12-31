require_relative 'card'
class Deck
  attr_accessor :deck
  def initialize
    @deck = full_deck
  end

  def to_s
    s = ""
    @deck.each {|c|
      s = s + c.to_s
    }
  end

  def shuffle
    d = Deck.new
    d.deck = d.deck.shuffle
    d
  end

  def shuffle!
    @deck.shuffle!
  end

  def full_deck
    index = 0
    tempDeck = []
    for rank in 1..13
      for suit in [:diamonds, :spades,:hearts,:clubs]
        tempDeck[index] = Card.new rank, suit
        index +=1
      end
    end
    tempDeck
  end

  def pop_card
    c = @deck.pop
    if c.nil?
      puts 'out of cards'
    end
    c
  end
end