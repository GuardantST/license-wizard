#ifndef NOTIFICATION_H
#define NOTIFICATION_H

// Note that ApiError is special (GRD_* status code can be encoded into
//   notification type int for ApiError, especially if ApiError would be
//   assigned INT_MIN, but prefer the notification struct)
enum class NotificationType
{
    None, // no actual notification
    LicenseInstalled, // for a specific license
    LicenseUpdated, // for a specific license
    LicenseUpdateAvailable, // for a specific license
    LicenseUpdateAvailableAll, // for all licenses (at least one)
    NoMoreLicenseUpdates, // for a specific license
    CannotCheckLicenseUpdate, // for a specific license
    CannotCheckLicenseUpdateAll, // for all licenses (at least one)
    CannotUpdateLicense, // for a specific license
    LicenseExtracted,
    ApiError, // GRD_* status code
    LicenseIdCopiedToClipboard,
    InternalError
};

// If notification type is not ApiError, status is unused and must be zero;
//   otherwise, status must contain the corresponding GrdStatus code
struct Notification
{
    Notification(NotificationType type, int status = 0) :
        m_type(type),
        m_status(type == NotificationType::ApiError ? status : 0)
    {
    }

    NotificationType m_type;
    int m_status;
};

#endif // NOTIFICATION_H
