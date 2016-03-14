class Mraa

  class Uart
    attr_reader :baudrate, :read_to, :write_to, :interchar_to
    attr_accessor :read_bufsize
  end

end