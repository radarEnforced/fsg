package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

////////////////////////////////////////////////////////////////////////////////

/** */
public class FragmentHeader extends Fragment
{
    private ImageView mImageViewBack = null;    ///<

    /** */
    public FragmentHeader() {}

    /** */
    @Override
    public View onCreateView( LayoutInflater inflater,
                              ViewGroup container,
                              Bundle savedInstanceState )
    {
        View rootView = inflater.inflate( R.layout.fragment_header, container, false );

        mImageViewBack = (ImageView)rootView.findViewById( R.id.fragment_header_img_back );
        mImageViewBack.setOnClickListener( new View.OnClickListener()
        {
            @Override
            public void onClick( View view )
            {
                getActivity().onBackPressed();
            }
        } );

        return rootView;
    }
}
