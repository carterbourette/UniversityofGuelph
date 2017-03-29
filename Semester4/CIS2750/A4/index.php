<?php
/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/
?>
<!DOCTYPE html>
<html>
    <head>
        <title>Login</title>
        <style>

            #page {
                width:100%;
                height:100vh;
                display:table;
            }
            fieldset {
                width:30%;
                min-height: 155px;
                min-width: 475px;
                margin: auto auto;
                border:1px solid;
                background: white;
            }
            fieldset legend {
                font-size:1.1rem;
                font-weight: 600;
            }

            input {
                width: 100%;
            }

            .display {
                display:table-cell;
                vertical-align: middle;
            }

            table {
                position: relative;
                top:1em;
            }
        </style>
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>
    <body>
        <div id="page">
            <div class="display">
                <fieldset>
                    <legend>Login to A3 Web Interface</legend>
                    <form action="process.php?form=login" method="post">
                        <table width="100%">
                            <tr>
                                <td align="right">
                                    <label for="username">Username:</label>
                                </td>
                                <td>
                                    <input id="username" type="text" name="userid" placeholder="Your name here..." />
                                </td>
                            </tr>
                            <tr colspacing>
                                <td align="center">
                                    <a href="process.php?view=addorremove.wpml">or signup here...</a>
                                </td>
                                <td align="right">
                                    <button>Submit</button>
                                </td>
                            </tr>
                        </table>
                    </form>
                </fieldset>
            </div>
        </div>

    </body>
</html>
