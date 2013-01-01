class Card
  WILD_RANK = 7
  GIVE_2_RANK = 6
  
  attr_accessor :rank, :suit
  def initialize rank, suit
    @rank = rank
    @suit = suit
    if Card.suit_to_s @suit == nil
      raise "invalid suit"
    end
  end

  def wild?
    @rank == WILD_RANK
  end
  
  def give_two?
    @rank == GIVE_2_RANK
  end
  
  def ==(c)
    c.rank == @rank && c.suit == @suit
  end
  
  def self.rank_to_s rank
    return {1=>"Ace", 11=>"Jack", 12=>"Queen", 13=>"King"}[rank] if rank<=1 || rank>=11
    rank.to_s
  end

  def self.suit_to_s suit
    {:spades=>"spades", :diamonds=>"diamonds", :hearts=>"hearts", :clubs =>"clubs"}[suit]
  end

  def to_s
    if rank>1 && rank<=10
      @rank.to_s + " of " + Card.suit_to_s(@suit)
    else
      "#{Card.rank_to_s(@rank)} of #{Card.suit_to_s(@suit)}"
    end
  end
end