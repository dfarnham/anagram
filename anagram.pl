#!/usr/bin/env perl

# one liner
# perl -ne 'chop;push(@{$h{join("",sort(split//))}},$_);END{print map{@$_>1?"@$_\n":()}values%h}' testWords

use strict;

my %h;
while (chomp(my $word = <>)) {
    push (@{$h{join('', digest($word))}}, $word);
}
print map { @$_ > 1 ? "@$_\n" : () } values %h;

# sorting the characters for every word seems pretty wanky,
# see the replacement digest idea in "anagram.c"
sub digest {
    my $word = shift;
    return sort(split(//, $word));
}
