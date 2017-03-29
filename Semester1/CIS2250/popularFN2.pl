#!/usr/bin/perl
#
#   Packages and modules
#
use strict;
use warnings;
use version;   our $VERSION = qv('5.16.0');   # This is the version of Perl to be used
use Text::CSV  1.32;   # We will be using the CSV module (version 1.32 or higher)
# to parse each line

#
#   readFile.pl
#      Author(s): Carter Bourette (0916638) & Mark Sansome (0916066)
#      Project: Lab Assignment 3 Task 1 Script
#      Date of Last Update: Monday, Febuary 1, 2016.
#
#      Functional Summary
#         readFile.pl takes in a CSV (comma separated version) file
#         and prints out the fields.
#         There are three fields:
#            1. name
#            2. gender (F or M)
#            3. number of people with this name
#
#         This code will also count the top 5 number of female and male
#         names in this file and print this out at the end.
#
#         The file represents the names of people in the population
#         for a particular year of birth in the United States of America.
#         Officially it is the "National Data on the relative frequency
#         of given names in the population of U.S. births where the individual
#         has a Social Security Number".
#
#      Commandline Parameters: 4
#         $ARGV[0] = Start Year (YYYY)
#         $ARGV[1] = End Year (YYYY)
#         $ARGV[2] = Increment (between Start and End)
#         $ARGV[3] = filename ($ARG.txt)
#
#      References
#         Name files from http://www.ssa.gov/OACT/babynames/limits.html
#

my $EMPTY = q{};
my $SPACE = q{ };
my $COMMA = q{,};

#
#   Variables to be used
#
my $filename     = $EMPTY;
my $classfilename= $EMPTY;
my @records;

my $startYear;
my $endYear;
my $inc;
my $compFile;

my $csv          = Text::CSV->new({ sep_char => $COMMA });


#
#   Functions
#

#   Open a file, return an array of lines, close file;
sub openFile {
    
    open my $names_fh, '<', $_[0]
    or die "Unable to open names file: $filename\n";
    
    my @csvRecords = <$names_fh>;
    
    close $names_fh or
    die "Unable to close: $_[0]\n";   # Close the input file
    
    
    return @csvRecords;
}

sub getIndex {
    my $num = $_[0];
    
    if ($num == 0) {
        return 0;
    } elsif ($num > 2000) {
        return 1;
    } elsif ($num >=1000 && $num <=2000) {
        return 2;
    } elsif ($num >= 500 && $num <= 999) {
        return 3;
    } elsif ($num >= 200 && $num <= 499) {
        return 4;
    } elsif ($num >= 100 && $num <= 199) {
        return 5;
    } elsif ($num >= 50 && $num <= 99) {
        return 6;
    } elsif ($num >= 11 && $num <= 49) {
        return 7;
    } elsif ($num >= 1 && $num <= 10) {
        return 8;
    }
    
}

#
#   Check that you have the right number of parameters
#
if ($#ARGV != 3 ) {
    print "Usage: popularFN1.pl <start year (YYYY)> <end year (YYYY)> <increment> <file>\n" or
    die "Print failure\n";
    exit;
} else {
    $startYear = $ARGV[0];
    $endYear = $ARGV[1];
    $inc = $ARGV[2];
    $compFile = $ARGV[3];
}

#
#   Open the file we are analyzing
#
@records = openFile($compFile);

my $count = 1;
my $female = 0;
my $male = 0;
my $found = 0;

print "\"Name\",\"Year\",\"Score\"\n";

#   For each person in the target file
foreach my $line ( @records ) {
    if ( $csv->parse($line) ) {
        my @master_fields = $csv->fields();

        #   For each year from start to end compare
        for (my $j = $startYear; $j <= $endYear; $j = $j + $inc){
            
            #   Open the year file, dump contents into @arr
            my @arr = openFile("yob".$j.".txt");
            foreach my $line ( @arr ) {
                if ( $csv->parse($line) ) {
                    my @master_fields2 = $csv->fields();
                    
                    if ($master_fields2[1] eq 'M') {
                        $male++;
                    } elsif ($master_fields2[1] eq 'F'){
                        $female++;
                    }
                    
                    #   Lets get the gender on every line and count males and females
                    if ($master_fields2[0] eq $master_fields[0] && $master_fields[1] eq $master_fields2[1]) {
                        if ($master_fields[1] eq 'F') {
                            print $master_fields[0].",".$j.",".getIndex($female);
                        } else {
                            print $master_fields[0].",".$j.",".getIndex($male);
                        }
                        $found = 1;
                        print "\n";
                        last;
                    }
                }
                $count++;
            } if ($found != 1) {
                print $master_fields[0].",".$j.",0";
                print "\n";
            }
            $found = 0;
            $male = 0;
            $female = 0;
        }
    }
}

#
#   End of Script
#
