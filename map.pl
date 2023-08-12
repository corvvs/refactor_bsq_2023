#!/usr/bin/perl
use warnings;
use strict;
die "program x y density" unless (scalar(@ARGV) == 3);

my ($x, $y, $density) = @ARGV;

my $char_empty     = ".";
my $char_obstacle  = "o";
my $char_full      = "x";

print "$y$char_empty$char_obstacle$char_full\n";
for (my $i = 0; $i < $y; $i++) {
    for (my $j = 0; $j < $x; $j++) {
        if (int(rand($y) * 2) < $density) {
            print $char_obstacle;
        }
        else {
            print $char_empty;
        }
    }
    print "\n";
}
