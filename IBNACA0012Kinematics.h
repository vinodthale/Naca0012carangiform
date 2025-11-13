// ---------------------------------------------------------------------
//
// Copyright (c) 2014 - 2023 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

#ifndef included_IBNACA0012Kinematics
#define included_IBNACA0012Kinematics

/////////////////////////////////////// INCLUDES ////////////////////////////////
#include "ibamr/ConstraintIBKinematics.h"

#include "ibtk/LDataManager.h"
#include "ibtk/ibtk_utilities.h"

#include <SAMRAI/hier/PatchHierarchy.h>
#include <SAMRAI/tbox/Array.h>
#include <SAMRAI/tbox/Database.h>
#include <SAMRAI/tbox/Pointer.h>

#include <iostream>
#include <map>
#include <vector>

namespace mu
{
class Parser;
} // namespace mu

///////////////////////////////////////////////////////////////// CLASS DEFORMATIONAL KINEMATICS //////////////////

namespace IBAMR
{
/*!
 * \brief IBNACA0012Kinematics is a concrete class which calculates the deformation velocity and updated shape
 * for NACA0012 airfoil with carangiform swimming motion. It also provides routines for maneuvering and food tracking cases.
 * 
 * Kinematics based on:
 *  Khalid et al. A bio-inspired study on tuna-mimetic soft robot with a compliant caudal fin. 
 *  J Fluids Structures, 66:19-35 (2016).
 *
 * Amplitude envelope: A(x/L) = 0.02 - 0.0825(x/L) + 0.1625(x/L)^2
 * Traveling wave: y(x,t) = A(x/L) * cos[2π(x/L - ft)]
 */

class IBNACA0012Kinematics : public ConstraintIBKinematics

{
public:
    /*!
     * \brief ctor. This is the only ctor for this object.
     */
    IBNACA0012Kinematics(const std::string& object_name,
                         SAMRAI::tbox::Pointer<SAMRAI::tbox::Database> input_db,
                         IBTK::LDataManager* l_data_manager,
                         SAMRAI::tbox::Pointer<SAMRAI::hier::PatchHierarchy<NDIM> > patch_hierarchy,
                         bool register_for_restart = true);

    /*!
     * \brief Destructor.
     */
    virtual ~IBNACA0012Kinematics();

    /*!
     * \brief Set kinematics velocity for NACA0012 carangiform fish.
     * \see IBAMR::ConstraintIBKinematics::setKinematicsVelocity
     */
    virtual void setKinematicsVelocity(const double time,
                                       const std::vector<double>& incremented_angle_from_reference_axis,
                                       const std::vector<double>& center_of_mass,
                                       const std::vector<double>& tagged_pt_position);

    /*!
     * \brief Get the kinematics velocity on the specified level.
     * \see IBAMR::ConstraintIBKinematics::getKinematicsVelocity
     */
    virtual const std::vector<std::vector<double> >& getKinematicsVelocity(const int level) const;

    /*!
     * \brief Set the shape of NACA0012 fish at the required time.
     * \see IBAMR::ConstraintIBKinematics::setShape
     */
    virtual void setShape(const double time, const std::vector<double>& incremented_angle_from_reference_axis);

    /*!
     * \brief Get the shape of NACA0012 fish at the required level.
     * \see IBAMR::ConstraintIBKinematics::getShape
     */
    virtual const std::vector<std::vector<double> >& getShape(const int level) const;

    /*!
     * \brief Override the ConstraintIBkinematics base class method.
     */
    virtual void putToDatabase(SAMRAI::tbox::Pointer<SAMRAI::tbox::Database> db);

private:
    /*!
     * \brief The default constructor is not implemented and should not be used.
     */
    IBNACA0012Kinematics();

    /*!
     * \brief The copy constructor is not implemented and should not be used.
     */
    IBNACA0012Kinematics(const IBNACA0012Kinematics& from);

    /*!
     * \brief The assignment operator is not implemented and should not be used.
     */
    IBNACA0012Kinematics& operator=(const IBNACA0012Kinematics& that);

    /*!
     * \brief Set data from restart.
     */
    void getFromRestart();

    /*!
     * \brief set NACA0012 fish body shape related data.
     */
    void setImmersedBodyLayout(SAMRAI::tbox::Pointer<SAMRAI::hier::PatchHierarchy<NDIM> > patch_hierarchy);

    /*!
     * \brief Set deformation kinematics velocity of the NACA0012 fish.
     */
    void setNACA0012SpecificVelocity(const double time,
                                     const std::vector<double>& incremented_angle_from_reference_axis,
                                     const std::vector<double>& center_of_mass,
                                     const std::vector<double>& tagged_pt_position);

    /*!
     * \brief Rotate the maneuver axis and calculate tangents in this orientation.
     */
    void transformManeuverAxisAndCalculateTangents(const double angleFromHorizontal);

    /*!
     * Current time (t) and new time (t+dt).
     */
    double d_current_time, d_new_time;

    /*!
     * Deformational velocity and shape vectors.
     */
    std::vector<std::vector<double> > d_kinematics_vel;
    std::vector<std::vector<double> > d_shape;

    /*!
     * Save COM, tagged point position and incremented angle from reference axis for restarted runs.
     */
    std::vector<double> d_center_of_mass, d_incremented_angle_from_reference_axis, d_tagged_pt_position;

    /*!
     * Eulerian Mesh width parameters.
     */
    std::vector<double> d_mesh_width;

    /*!
     * The following map is used to store NACA0012 fish body shape specific data.
     * The arc length 's' varies from 0 - 1. In the std::map the arc length 's' is used as a key.
     * d_ImmersedBodyData is used to store the no of material points which represents a cross section. The
     * width of cross section of NACA0012 varies with arc length.
     */
    std::map<double, int> d_ImmersedBodyData;

    /*!
     * Initial orientation of the body axis
     */
    double d_initAngle_bodyAxis_x;

    /*!
     * Boolean value indicating if NACA0012 fish is maneuvering or not.
     * If fish is maneuvering then the traveling wave will be along a curved axis, otherwise it will be on a straight
     * line
     */
    bool d_bodyIsManeuvering;

    /*!
     * Boolean to indicate if shape of maneuver axis is changing. The maneuver axis will change shape in food tracking
     * cases.
     */
    bool d_maneuverAxisIsChangingShape;

    /*!
     * Vector of coordinates defining the axis of maneuvering. The reference axis will rotate with body omega.
     * The coordinates of the rotated maneuver axis is stored separately.
     */
    std::vector<std::vector<double> > d_maneuverAxisReferenceCoordinates_vec, d_maneuverAxisTransformedCoordinates_vec;

    /*!
     * map of tangents along the body/maneuver axis in rotated frame. The key used is arc length 's' and it stores only
     * the abs(theta).
     * Sign of tangent is stored separately. This is done to avoid a lot of if conditions needed to determine the
     * quadrant of the
     * angle.
     */
    std::map<double, double> d_map_transformed_tangent;

    /*!
     * map of tangents along the body/maneuver axis in reference/unrotated frame.The key used is arc length 's' and it
     * stores only the abs(theta).
     * Sign of tangent is stored separately. This is done to avoid a lot of if conditions needed to determine the
     * quadrant of the
     * angle.
     */
    std::map<double, double> d_map_reference_tangent;

    /*!
     * Sign of tangent vector in rotated frame. The key used is arc length 's'. 'mapped_value' is a vector which has
     * sign of t_x and t_y
     * respectively.
     */
    std::map<double, std::vector<int> > d_map_transformed_sign;

    /*!
     * Sign of tangent vector in reference/unrotated frame. The key used is arc length 's'. 'mapped_value' is a vector
     * which has sign of t_x and t_y
     * respectively.
     */
    std::map<double, std::vector<int> > d_map_reference_sign;

    /*!
     * mu::Parser object which evaluates the maneuvering axis equation.
     */
    mu::Parser* d_maneuvering_axis_parser;

    /*!
     * mu::Parser object which evaluates the shape of the body.
     */
    mu::Parser* d_body_shape_parser;

    /*!
     * The mu::Parser objects which evaluate the data-setting functions.
     */
    std::vector<mu::Parser*> d_deformationvel_parsers;
    std::vector<mu::Parser*> d_all_parsers;

    /*!
     * Time and position variables.
     */
    mutable double d_parser_time;
    mutable IBTK::Point d_parser_posn;
    mutable IBTK::Point d_parser_normal;

    /*!
     * Array containing initial coordinates of the food location.
     */
    SAMRAI::tbox::Array<double> d_food_location;

    /*!
     * NACA0012 Carangiform swimming parameters
     * Amplitude envelope coefficients: A(x/L) = a0 + a1*(x/L) + a2*(x/L)^2
     * Reference: Khalid et al. (2016), J. Fluids Structures 66:19-35
     */
    double d_a0, d_a1, d_a2;           // Amplitude envelope coefficients
    double d_wavelength;                // Wavelength λ (typically equals body length L)
    double d_frequency;                 // Undulation frequency f (Hz)

}; // IBNACA0012Kinematics

} // namespace IBAMR
#endif // #ifndef included_IBNACA0012Kinematics