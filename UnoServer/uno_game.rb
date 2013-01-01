require_relative 'deck'
require_relative 'player'
require_relative 'base_player'

class UnoGame
  @@rand = Random.new()
  def initialize(player_one=PlayerA, player_two=PlayerA, start_turn=:random)
    deck = Deck.new
    deck.shuffle!
    
    #start game
    @player1 = player_one.new
    @player2 = player_two.new

    7.times do
      @player1.add_card deck.pop_card
      @player2.add_card deck.pop_card
    end

    @pile = deck.pop_card
    @draw = deck.deck
    if start_turn == :random
      @turn = [:player_one_turn,:player_two_turn][@@rand.rand(0..1)]
    else
      @turn = :player_one_turn
    end
  end

  def other_turn turn
    if turn==:player_one_turn
      :player_two_turn
    elsif turn == :player_two_turn
      :player_one_turn
    end
  end

  def run(debug = false)
    game_status = :keep_playing
    while game_status == :keep_playing
      game_status = next_turn
      puts us.to_s + "\n"*2 if debug      
    end
    return game_status #win on :player_one_turn or :player_two_turn
  end
  
  def check played_card, top_card
    played_card.rank==top_card.rank || played_card.suit == top_card.suit || played_card.wild?
  end
  
  def next_turn
    #start turn switching code
    if @turn == :player_one_turn
      player = @player1
    elsif @turn == :player_two_turn
      player = @player2
    else
      raise "weird turn"
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
