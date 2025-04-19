class MealyError(Exception):
    pass


class StateMachine:
    def __init__(self):
        self.state = 'A'

    def close(self):
        if self.state == 'A':
            self.state = 'B'
            return 0
        if self.state == 'B':
            self.state = 'E'
            return 2
        if self.state == 'C':
            self.state = 'H'
            return 4
        if self.state == 'E':
            self.state = 'H'
            return 7
        if self.state == 'F':
            self.state = 'C'
            return 9
        if self.state == 'G':
            self.state = 'H'
            return 10
        raise MealyError('close')

    def turn(self):
        if self.state == 'B':
            self.state = 'C'
            return 1
        if self.state == 'C':
            self.state = 'D'
            return 3
        if self.state == 'D':
            self.state = 'E'
            return 5
        if self.state == 'E':
            self.state = 'F'
            return 6
        if self.state == 'F':
            self.state = 'G'
            return 8
        if self.state == 'G':
            self.state = 'A'
            return 11
        raise MealyError('turn')


def main():
    return StateMachine()


def raises(function, error):
    output = None
    try:
        output = function()
    except Exception as e:
        assert type(e) == error
    assert output is None
    
def test():
    o = main()
    assert o.close() == 0
    assert o.close() == 2
    assert o.close() == 7
    raises(lambda: o.close(), MealyError)
    raises(lambda: o.turn(), MealyError)
    o = main()
    assert o.close() == 0
    assert o.turn() == 1
    assert o.turn() == 3
    assert o.turn() == 5
    assert o.turn() == 6
    assert o.turn() == 8
    assert o.close() == 10
    o.state = 'F'
    assert o.close() == 9
    assert o.close() == 4
    o.state = 'G'
    assert o.turn() == 11