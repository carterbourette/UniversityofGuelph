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
#      Project: Lab Assignment 2 Task 3 Script
#      Date of Last Update: Monday, January 27, 2016.
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

my $female_count = 0;
my $male_count = 0;

#   For each person in the target file
foreach my $line ( @records ) {
    if ( $csv->parse($line) ) {
        my @master_fields = $csv->fields();
        
        #   First victim, print name, gender, then check position by year
        print $master_fields[0].",";    #   print name
        print $master_fields[1];        #   print gender
        
        #   For each year from start to end compare
        for (my $j = $startYear; $j <= $endYear; $j = $j + $inc){
            
            #   Open the year file, dump contents into @arr
            my @arr = openFile("yob".$j.".txt");
            
            my $lineNum = 0;
            #   For each line in the variable year
            foreach my $line ( @arr ) {
                if ( $csv->parse($line) ) {
                    my @master_fields2 = $csv->fields();
                    
                    #   Lets get the gender on every line and count males and females
                    if ($master_fields2[1] eq "F") {
                        $female_count++;
                    } else {
                        $male_count++;
                    }
                    
                    #   Found a match! Print it. ( Target Name == Name in File + Gender )
                    if ($master_fields2[0] eq $master_fields[0] && $master_fields2[1] eq $master_fields[1]) {
                        
                        print ",",$j.",";           #   print year
                        
                        if ($master_fields2[1] eq "M"){
                            print $male_count;
                            $male_count = 0;
                        } else {
                            print $lineNum+1;    #   print position
                            $female_count = 0;
                        }
                        last;
                    }
                }
                $lineNum++;
            }
        }
        print "\n";
    }
}

#
#   End of Script
#
