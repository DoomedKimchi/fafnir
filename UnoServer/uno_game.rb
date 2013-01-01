require_relative 'deck'
require_relative 'player_a'
require_relative 'base_player'
class UnoGame
  def initialize
    deck = Deck.new
    deck.shuffle!
    
    #start game
    @player1 = PlayerA.new
    @player2 = PlayerA.new

    7.times do
      @player1.add_card deck.pop_card
      @player2.add_card deck.pop_card
    end

    @pile = deck.pop_card
    @draw = deck.deck

    @turn = :player_two_turn
  end

  def other_turn turn
    if turn==:player_one_turn
      :player_two_turn
    elsif turn == :player_two_turn
      :player_one_turn
    end
  end

  def next_turn
    #start turn switching code
    if @turn == :player_one_turn
    player = @player1
    elsif @turn == :player_two_turn
    player = @player2
    else
      player = nil
    end
    #end
    
    player.update_game_state :top_card => @pile.clone
    card = player.play_card
    #start give card
    if card.nil?
      draw = @draw.pop
      player.add_card draw
    else
      @draw.push @pile
      @draw.shuffle!
      @pile = card
      if player.win?
        return @turn
      end
    end
    #end
    @turn = other_turn @turn
    return :keep_playing
  end

  def to_s
    "draw:(#{@draw.size}) #{@draw}\npile:(1) #{@pile}\nplayer1:\n#{@player1}player2:\n#{@player2}"
  end
end