--Interface alligns
Allign = { LEFT=0, CENTER=1, RIGHT=2, FREE=3 }

GL_READ_ONLY = 0x88B8;
GL_WRITE_ONLY = 0x88B9;
GL_READ_WRITE = 0x88BA;

interface_size = {x = 1920, y = 1080};

function tostringp(num, p)
	return tostring(p*math.floor(num/p+0.5));
end;


Color = {
		Black = vec4.new(0,0,0,1),
		White = vec4.new(1,1,1,1),
		Red = vec4.new(1,0,0,1),
		Green = vec4.new(0,1,0,1),
		Blue = vec4.new(0,0,1,1),
		Gray = vec4.new(0.5,0.5,0.5, 1),
		Transparent = vec4.new(1,1,1,0)
		};

--SFML keys
Key = {
        Unknown = -1, -- Unhandled key
        A = 0,        -- The A key
        B = 1,            -- The B key
        C = 2,            -- The C key
        D = 3,            -- The D key
        E = 4,            -- The E key
        F = 5,            -- The F key
        G = 6,            -- The G key
        H = 7,            -- The H key
        I = 8,            -- The I key
        J = 9,            -- The J key
        K = 10,            -- The K key
        L = 11,            -- The L key
        M = 12,            -- The M key
        N = 13,            -- The N key
        O = 14,            -- The O key
        P = 15,            -- The P key
        Q = 16,            -- The Q key
        R = 17,            -- The R key
        S = 18,            -- The S key
        T = 19,            -- The T key
        U = 20,            -- The U key
        V = 21,            -- The V key
        W = 22,            -- The W key
        X = 23,            -- The X key
        Y = 24,            -- The Y key
        Z = 25,            -- The Z key
        Num0 = 26,         -- The 0 key
        Num1 = 27,         -- The 1 key
        Num2 = 28,         -- The 2 key
        Num3 = 29,         -- The 3 key
        Num4 = 30,         -- The 4 key
        Num5 = 31,         -- The 5 key
        Num6 = 32,         -- The 6 key
        Num7 = 33,         -- The 7 key
        Num8 = 34,         -- The 8 key
        Num9 = 35,         -- The 9 key
        Escape = 36,       -- The Escape key
        LControl = 37,     -- The left Control key
        LShift = 38,       -- The left Shift key
        LAlt = 39,         -- The left Alt key
        LSystem = 40,      -- The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl = 41,     -- The right Control key
        RShift = 42,       -- The right Shift key
        RAlt = 43,         -- The right Alt key
        RSystem = 44,      -- The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu = 45,         -- The Menu key
        LBracket = 46,     -- The [ key
        RBracket = 47,     -- The ] key
        Semicolon = 48,    -- The ; key
        Comma = 49,        -- The , key
        Period = 50,       -- The . key
        Quote = 51,        -- The ' key
        Slash = 52,        -- The / key
        Backslash = 53,    -- The \ key
        Tilde = 54,        -- The ~ key
        Equal = 55,        -- The = key
        Hyphen = 56,       -- The - key (hyphen)
        Space = 57,        -- The Space key
        Enter = 58,        -- The Enter/Return keys
        Backspace = 59,    -- The Backspace key
        Tab = 60,          -- The Tabulation key
        PageUp = 61,       -- The Page up key
        PageDown = 62,     -- The Page down key
        End = 63,          -- The End key
        Home = 64,         -- The Home key
        Insert = 65,       -- The Insert key
        Delete = 66,       -- The Delete key
        Add = 67,          -- The + key
        Subtract = 68,     -- The - key (minus, usually from numpad)
        Multiply = 69,     -- The * key
        Divide = 70,       -- The / key
        Left = 71,         -- Left arrow
        Right = 72,        -- Right arrow
        Up = 73,           -- Up arrow
        Down = 74,         -- Down arrow
        Numpad0 = 75,      -- The numpad 0 key
        Numpad1 = 76,      -- The numpad 1 key
        Numpad2 = 77,      -- The numpad 2 key
        Numpad3 = 78,      -- The numpad 3 key
        Numpad4 = 79,      -- The numpad 4 key
        Numpad5 = 80,      -- The numpad 5 key
        Numpad6 = 81,      -- The numpad 6 key
        Numpad7 = 82,      -- The numpad 7 key
        Numpad8 = 83,      -- The numpad 8 key
        Numpad9 = 84,      -- The numpad 9 key
        F1 = 85,           -- The F1 key
        F2 = 86,           -- The F2 key
        F3 = 87,           -- The F3 key
        F4 = 88,           -- The F4 key
        F5 = 89,           -- The F5 key
        F6 = 90,           -- The F6 key
        F7 = 91,           -- The F7 key
        F8 = 92,           -- The F8 key
        F9 = 93,           -- The F9 key
        F10 = 94,          -- The F10 key
        F11 = 95,          -- The F11 key
        F12 = 96,          -- The F12 key
        F13 = 97,          -- The F13 key
        F14 = 98,          -- The F14 key
        F15 = 99,          -- The F15 key
        Pause = 100,        -- The Pause key

        KeyCount = 101     -- Keep last -- the total number of keyboard keys
    };