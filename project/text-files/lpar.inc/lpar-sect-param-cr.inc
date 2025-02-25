
# This section defines general LE-CODE parameters. The corresponding options
# have a higher priority. Remove or comment-out a parameter if its value
# should not be changed. All values will be limited to the allowed ranges.

#------------------------------------------------------------------------------

# First we define a limitation mode. This mode defines the allowed values for
# the other parameters of this section:
#
#   LE$PRODUCTIVE   : Exclude test and experimental values.
#   LE$TESTING      : Allow test values, but exclude experimental values.
#   LE$EXPERIMENTAL : Allow all values.
#   LE$AUTOMATIC    : Enable automatic detection by analyzing all values.
#
# Values set by an option are never limited. See parameter descriptions for
# limitation details.

LIMIT-MODE	= %s

#------------------------------------------------------------------------------

# LE-CODE supports cheat codes as sequence of D-Pad keys in combination with
# ALT keys. Here you can define, which type of cheat codes are allowed:
#  0: Almost all cheat codes are disabled.
#  1: Only cheat codes without impact to game play are allowed.
#  2: All cheat codes are allowed. (Not possible if LIMIT-MODE==LE$PRODUCTIVE).

CHEAT-MODE	= %d

# Define probabilities for engine classes. A list for »100cc,150cc,mirror« is
# expected. If 200cc is enabled, the values are for »150cc,200cc,mirror«. Any
# number is accepted. They are normalized to get a total of 100 percent.
# Use »0,1,0« to force 150cc. Use »0,0,0« to reset to Nintendo's VR based
# choice. Option --engine will overrides these settings.

ENGINE		= %u,%u,%u

# Enable (1) or disable (0) 200cc support. Option --200cc will overrides this
# setting. LE-CODE hasn't implemented this feature yet!

ENABLE-200CC	= %u

# Enable (1) or disable (0) the performance monitor at Wii and Wii U. Enabling
# is only possible if LIMIT-MODE is LE$TESTING or LE$EXPERIMENTAL. The special
# value 2 enables it for Dolphin too, but only on LE$EXPERIMENTAL. It doesn't
# work correctly with Dolphin. Option --perf-mon will overrides this setting.

PERF-MONITOR	= %u

# Enable (1) or disable (0) Time Trial for custom tracks. Option --custom-tt
# will overrides this setting.

CUSTOM-TT	= %u

# Enable (1) or disable (0) support for Extended Presence Flags. Disable it
# only for tests! If LIMIT-MODE==LE$PRODUCTIVE, XPFLAGS is always enabled.
# Option --xpflags overrides this setting.

XPFLAGS		= %u

# Define the number of races that a previously used track is blocked. LE-CODE
# will try to find another possible track among the selected tracks. Values
# between 0 (deactivated at all) and %u are allowed. Chat messages can clear
# the track list and enable or disable this feature.

BLOCK-TRACK	= %u

# Enables (SPEEDO$0 .. SPPEDO$3) or disables (SPEEDO$OFF) the speedometer.
# If enabled, the speedometer is displayed at bottom right of the screen
# using format »123.123 km/h«. The digit behind SPEEDO$ defines the number
# of fraction digits.
# Option --speedometer overrides this setting.

SPEEDOMETER	= SPEEDO$%s

# Define a debug mode. Debug output is displayed below the speedometer. It is
# defined by sections [DEBUG-*]. This parameter defines the general behaviour.
# Possible values are DEBUG$OFF, DEBUG$ENABLED and DEBUG$1 to DEBUG$4.
# DEBUG$OFF disables the debug output at all. All other values enable debug
# output and define the start configuration.
# Option --debug overrides this setting.

DEBUG		= DEBUG$%s

# Enable (1) or disable (0) built-in item cheat.

ITEM-CHEAT	= %u

# Allow (1) or forbid (0) players to drag blue shells behind them.
# LE-CODE default is 1.

DRAG-BLUE-SHELL	= %u

# Define the time in frames a player is small after being struck by a
# thundercloud. Only values between 1 and 32767 (0x7fff) are accepted.
# MKW uses 612 (10.2s) and LE-CODE default is 300 (5.0s).

THCLOUD-TIME	= %u # %.2fs

# Since build 34, LE-CODE supports texture hacks for original Nintendo tracks
# and arenas. This new feature can be disabled by value LE$DISABLE (default)
# or enabled by value LE$ENABLE. Additonally you can append »|LE$ALTERABLE«
# to allow the user to enable or disable this feature by controller cheat
# codes. Append »|LE$EXCLUDE« to exclude the original track from the random
# selection.

BT-TEXTURES	= %s
VS-TEXTURES	= %s

# Disable (0) or enable (1) the blocking of recent texture hacks. If disabled
# all online players select always the same texture variant. If enabled, then
# a texture variant will be blocked for the next 3 races. However, this has
# the disadvantage that players with different pasts may select different
# variants. But this should go away after a few races.

BLOCK-TEXTURES	= %u

