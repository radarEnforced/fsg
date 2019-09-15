package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

////////////////////////////////////////////////////////////////////////////////

/** */
public class DialogAskYesNo extends DialogFragment
{
    /** */
    public interface DialogAbortListener
    {
        public void onDialogPositiveClick( DialogFragment dialog );
        public void onDialogNegativeClick( DialogFragment dialog );
    }

    DialogAbortListener mListener;      ///<

    private String mQuestion = "";      ///<

    @Override
    public void onCreate( Bundle savedInstanceState )
    {
        super.onCreate( savedInstanceState );
    }

    @Override
    public Dialog onCreateDialog( Bundle savedInstanceState )
    {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage( mQuestion )
                .setPositiveButton( getString( R.string.yes ), new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Send the positive button event back to the host activity
                        mListener.onDialogPositiveClick( DialogAskYesNo.this );
                    }

                })
                .setNegativeButton( getString( R.string.no ), new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Send the negative button event back to the host activity
                        mListener.onDialogNegativeClick( DialogAskYesNo.this );
                    }

                });
        // Create the AlertDialog object and return it
        return builder.create();

    }

    public void setListener( DialogAbortListener listener )
    {
        mListener = listener;
    }

    public void setQuestion( String question )
    {
        mQuestion = question;
    }
}
