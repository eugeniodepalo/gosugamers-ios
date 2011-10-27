// PFUser.h
// Copyright 2011 Parse, Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "PFObject.h"
#import "PF_Facebook.h"

/*!
 @class PFUser
 A Parse Framework User Object that is a local representation of a user persisted to the Parse cloud. This class
 is a subclass of a PFObject, and retains the same functionality of a PFObject, but also extends it with various
 user specific methods, like authentication, signing up, and validation uniqueness.
 @abstract A Parse User Object that can be persisted to the Parse platform.
 */


@interface PFUser : PFObject {
    NSString *password;
    NSString *sessionToken;
    NSString *facebookId;
    NSString *facebookAccessToken;
    NSDate *facebookExpirationDate;
    BOOL isNew;
@private
    BOOL isCurrentUser;
    BOOL deleteFacebook;
}

@property (nonatomic, retain) NSString *password;
@property (nonatomic, retain) NSString *sessionToken;
@property (readonly, retain) NSString *facebookAccessToken;
@property (readonly, retain) NSDate *facebookExpirationDate;
@property (readonly, retain) NSString *facebookId;
@property (readonly, assign) BOOL isNew;

// Not synthesized, just sugar for accessing data
@property (nonatomic, retain) NSString *username;
@property (nonatomic, retain) NSString *email;

/*!
 @abstract Initializes a new PFUser object.
 @result Returns a new PFUser object.
 */
- (id)init;

/*!
 @abstract Gets the currently logged in user from disk and returns an instance of it.
 @result Returns a PFUser that is the currently logged in user. If there is none, returns nil.
 */
+ (id)currentUser;

/*!
 @abstract Makes a request to login a user with specified credentials. Returns an instance
           of the successfully logged in PFUser. This will also cache the user locally so 
           that calls to userFromCurrentUser will use the latest logged in user.
 @param username The username of the user.
 @param password The password of the user.
 @result Returns an instance of the PFUser on success. If login failed for either wrong password or wrong username, returns nil.
 */
+ (PFUser *)logInWithUsername:(NSString *)username
                     password:(NSString *)password;

/*!
 @abstract Makes a request to login a user with specified credentials. Returns an
           instance of the successfully logged in PFUser. This will also cache the user 
           locally so that calls to userFromCurrentUser will use the latest logged in user.
 @param username The username of the user.
 @param password The password of the user.
 @param error The error object to set on error.
 @result Returns an instance of the PFUser on success. If login failed for either wrong password or wrong username, returns nil.
 */
+ (PFUser *)logInWithUsername:(NSString *)username
                     password:(NSString *)password
                        error:(NSError **)error;

/*!
 @abstract Makes an asynchronous request to login a user with specified credentials.
           Returns an instance of the successfully logged in PFUser. This will also cache 
           the user locally so that calls to userFromCurrentUser will use the latest logged in user.
 @param username The username of the user.
 @param password The password of the user.
 */
+ (void)logInWithUsernameInBackground:(NSString *)username
                             password:(NSString *)password;

/*!
 @abstract Makes an asynchronous request to login a user with specified credentials.
           Returns an instance of the successfully logged in PFUser. This will also cache 
           the user locally so that calls to userFromCurrentUser will use the latest logged in user. 
           The selector for the callback should look like: myCallback:(PFUser *)user error:(NSError **)error
 @param username The username of the user.
 @param password The password of the user.
 @param target Target object for the selector.
 @param selector The selector that will be called when the asynchrounous request is complete.
 */
+ (void)logInWithUsernameInBackground:(NSString *)username
                             password:(NSString *)password
                               target:(id)target
                             selector:(SEL)selector;


/*!
 @abstract  Gets the instance of the Facebook object (from the Facebook SDK) that Parse uses. 
 @result    The Facebook instance
 */
+ (PF_Facebook *)facebook;

/*!
 @abstract  Gets the instance of the Facebook object (from the Facebook SDK) that Parse uses. 
 @param     delegate Specify your own delegate for the Facebook object.
 @result    The Facebook instance
 */
+ (PF_Facebook *)facebookWithDelegate:(id<PF_FBSessionDelegate>)delegate;

/*!
 @abstract  Logs in a user using Facebook. This method delegates to the Facebook SDK to authenticate
            the user, and then automatically logs in (or creates, in the case where it is a new user)
            a PFUser. The selector for the callback should look like: (PFUser *)user error:(NSError **)error
 
 @param     permissions The permissions required for Facebook log in. This passed to the authorize method on 
            the Facebook instance.
 @param     target      Target object for the selector
 @param     selector    The selector that will be called when the asynchrounous request is complete.
 */
+ (void)logInWithFacebook:(NSArray *)permissions target:(id)target selector:(SEL)selector;

/*!
 @abstract  Links Facebook to an existing PFUser. This method delegates to the Facebook SDK to authenticate
            the user, and then automatically links the account to the PFUser.
            The selector for the callback should look like: (NSNumber *)result error:(NSError *)error
 
 @param     permissions The permissions required for Facebook log in. This passed to the authorize method on 
            the Facebook instance.
 @param     target      Target object for the selector
 @param     selector    The selector that will be called when the asynchrounous request is complete.
 */
- (void)linkToFacebook:(NSArray *)permissions target:(id)target selector:(SEL)selector;

/*!
 @abstract  Unlinks the PFUser from a Facebook account. 
 @result    Returns true if the unlink was successful.
 */
- (BOOL)unlinkFromFacebook;

/*!
 @abstract  Unlinks the PFUser from a Facebook account. 
 @param     error Error object to set on error.
 @result    Returns true if the unlink was successful.
 */
- (BOOL)unlinkFromFacebookWithError:(NSError **)error;

/*!
 @abstract  Makes an asynchronous request to unlink a user from a Facebook account. 
 @param     target      Target object for the selector
 @param     selector    The selector that will be called when the asynchrounous request is complete.
 */
- (void)unlinkFromFacebookInBackgroundWithTarget:(id)target selector:(SEL)selector;

/*!
 @abstract Send a password reset request for a specified email. If a user account exists with that email,
           an email will be sent to that address with instructions on how to reset their password.
 @param email Email of the account to send a reset password request.
 @result Returns true if the reset email request is successful. False if no account was found for the email address.
 */
+ (BOOL)requestPasswordResetForEmail:(NSString *)email;

/*!
 @abstract Send a password reset request for a specified email and sets an error object. If a user
           account exists with that email, an email will be sent to that address with instructions 
           on how to reset their password.
 @param email Email of the account to send a reset password request.
 @param error Error object to set on error.
 @result Returns true if the reset email request is successful. False if no account was found for the email address.
 */
+ (BOOL)requestPasswordResetForEmail:(NSString *)email error:(NSError **)error;

/*!
 @abstract Send a password reset request asynchronously for a specified email and sets an
           error object. If a user account exists with that email, an email will be sent to 
           that address with instructions on how to reset their password.
 @param email Email of the account to send a reset password request.
 */
+ (void)requestPasswordResetForEmailInBackground:(NSString *)email;

/*!
 @abstract Send a password reset request asynchronously for a specified email and sets an error object.
           If a user account exists with that email, an email will be sent to that address with instructions
           on how to reset their password.
 @param email Email of the account to send a reset password request.
 @param target Target object for the selector.
 @param selector The selector that will be called when the asynchronous request is complete. It should have the following signature: (void)callbackWithResult:(NSNumber *)result error:(NSError **)error. error will be nil on success and set if there was an error. [result boolValue] will tell you whether the call succeeded or not.
 */
+ (void)requestPasswordResetForEmailInBackground:(NSString *)email withTarget:(id)target selector:(SEL)selector;

/*!
 @abstract Logs out the currently logged in user on disk.
 */
+ (void)logOut;

/*!
 @abstract Whether the user is an authenticated object for the device. An authenticated PFUser is one that is obtained via
           a signUp or logIn method. An authenticated object is required in order to save (with altered values) or delete it.
 @result Returns whether the user is authenticated.
 */
- (BOOL)isAuthenticated;

/*!
 @abstract Whether the user has their account linked to Facebook.
 @result   True if the user has their account linked to Facebook.
*/
- (BOOL)hasFacebook;

/*!
 @abstract Signs up the user. Make sure that password and username are set. This will also enforce that the username isn't already taken. 
 @result Returns true if the sign up was successful.
 */
- (BOOL)signUp;

/*!
 @abstract Signs up the user. Make sure that password and username are set. This will also enforce that the username isn't already taken.
 @param error Error object to set on error. 
 @result Returns whether the sign up was successful.
 */
- (BOOL)signUp:(NSError **)error;

/*!
 @abstract Signs up the user asynchronously. Make sure that password and username are set. This will also enforce that the username isn't already taken.
 */
- (void)signUpInBackground;

/*!
 @abstract Signs up the user asynchronously. Make sure that password and username are set. This will also enforce that the username isn't already taken.
 @param target Target object for the selector.
 @param selector The selector that will be called when the asynchrounous request is complete. It should have the following signature: (void)callbackWithResult:(NSNumber *)result error:(NSError **)error. error will be nil on success and set if there was an error. [result boolValue] will tell you whether the call succeeded or not.
 */
- (void)signUpInBackgroundWithTarget:(id)target selector:(SEL)selector;

/*!
 @abstract Setter for the password property.
 @param newPassword The password to set.
 */
- (void)setPassword:(NSString *)newPassword;
- (NSString *)password;

#if NS_BLOCKS_AVAILABLE
/*!
 @abstract Makes an asynchronous request to login a user with specified credentials.
 Returns an instance of the successfully logged in PFUser. This will also cache 
 the user locally so that calls to userFromCurrentUser will use the latest logged in user. 
 @param username The username of the user.
 @param password The password of the user.
 @param block The block to execute. The block should have the following argument signature: (PFUser *user, NSError *error) 
 */
+ (void)logInWithUsernameInBackground:(NSString *)username password:(NSString *)password block:(PFUserResultBlock)block;

/*!
 @abstract Send a password reset request asynchronously for a specified email.
 If a user account exists with that email, an email will be sent to that address with instructions
 on how to reset their password.
 @param email Email of the account to send a reset password request.
 @param block The block to execute. The block should have the following argument signature: (BOOL succeeded, NSError *error) 
 */
+ (void)requestPasswordResetForEmailInBackground:(NSString *)email block:(PFBooleanResultBlock)block;

/*!
 @abstract Signs up the user asynchronously. Make sure that password and username are set. This will also enforce that the username isn't already taken.
 @param block The block to execute. The block should have the following argument signature: (BOOL succeeded, NSError *error) 
 */
- (void)signUpInBackgroundWithBlock:(PFBooleanResultBlock)block;

/*!
 @abstract  Logs in a user using Facebook. This method delegates to the Facebook SDK to authenticate
            the user, and then automatically logs in (or creates, in the case where it is a new user)
            a PFUser.
 @param     permissions The permissions required for Facebook log in. This passed to the authorize method on 
            the Facebook instance.
 @param     block The block to execute. The block should have the following argument signature:
            (PFUser *user, NSError *error) 
 */
+ (void)logInWithFacebook:(NSArray *)permissions block:(PFUserResultBlock)block;

/*!
 @abstract  Links Facebook to an existing PFUser. This method delegates to the Facebook SDK to authenticate
 the user, and then automatically links the account to the PFUser.
 @param     permissions The permissions required for Facebook log in. This passed to the authorize method on 
 the Facebook instance.
 @param     block The block to execute. The block should have the following argument signature:
            (BOOL *success, NSError *error) 
 */
- (void)linkToFacebook:(NSArray *)permissions block:(PFBooleanResultBlock)block;

/*!
 @abstract  Makes an asynchronous request to unlink a user from a Facebook account. 
 @param     block The block to execute. The block should have the following argument signature: (BOOL succeeded, NSError *error) 
 */
- (void)unlinkFromFacebookWithBlock:(PFBooleanResultBlock)block;
    
#endif

@end
