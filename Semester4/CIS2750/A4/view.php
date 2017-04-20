<?php
/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

     /**
      * transferSession
      * Transfer the get session to the next page through url param list.
      *
      * IN: $arr $_GET.
      * RETURN: (String) url list.
      *
      **/
     function transferSession($arr, $arg=null) {
         $string = "";
         foreach ($arr as $key=>$value) {
             if ($key != "form" && $key != "view" && $key != "sortchange") {
                $string = $string . "&" . $key . '=' . $value;
             }
         }
         if (null === $arg) {
             echo $string;
         } else {
             return $string;
         }
     }

    /**
     * render
     * Run the C translator to produce and load the .wpml page.
     *
     * IN: (String) Name of .wpml.
     * RETURN: NONE
     *
     **/
    function render($page) {
        exec('./a3 ' . $page, $out);
        foreach ($out as $line) {
            $arr = explode("PHPCALL",$line);
            foreach($arr as $tok) {
                $size = count($tok)-1;
                if($tok && $tok[0] == '_' && $tok[$size] == '_') {
                    eval(substr($tok,1,$size-1));
                } else {
                    echo $tok;
                }
            }
        }
    }
    //  If the view is specified, just render it.
    if (isset($_GET['view']) && isset($_GET['userid']) && $_GET['userid'] != "") {
        if(isset($_GET['sortchange'])) {
            if ((!isset($_GET['sort'])) || (isset($GET['sort']) && $_GET['sort'] == 'chrono')) {
                header("Location:view.php?" . transferSession($_GET,1) . "&sort=alpha");
            } else {
                header("Location:view.php?" . transferSession($_GET,1) . "&sort=chrono");
            }
        }
        render($_GET['view']);
    } else {
        /*  Delegate the view params  */
        if (!isset($_GET['userid']) || isset($_GET['userid']) && $_GET['userid'] == "") {
            if (isset($_GET['view']) && $_GET['view'] == 'addorremove.wpml') {
                render($_GET['view']);
            } else {
                //  No UserID specified, log them out
                header("Location: index.php");
            }
        } else {
            //  If the stream and message is specifed get them and render
            if(isset($_GET['sortchange'])) {
                echo "now here";
                if ((!isset($_GET['sort'])) || (isset($GET['sort']) && $_GET['sort'] == "chrono")) {
                    header("Location:view.php?" . transferSession($_GET,1) . "&sort=alpha");
                } else {
                    header("Location:view.php?" . transferSession($_GET,1) . "&sort=chrono");
                }
            }
            render('stream.wpml');
        }
    }

?>
